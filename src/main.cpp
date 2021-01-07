#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"
#include <ctime>
#include "Twiddle.h"


// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

void run_car(uWS::WebSocket<uWS::SERVER> &ws,PID &pid,double cte,double prev_steering)
{
  //in this funciton we publish the message to simulator to run with a specific steering value.
  
  //pid calculating the steering angle
  
  pid.UpdateError(cte);
    
  double steer_value = -1*pid.TotalError();
  //msg
  json msgJson;
  msgJson["steering_angle"] = steer_value;
  msgJson["throttle"] = 0.3;
  auto msg = "42[\"steer\"," + msgJson.dump() + "]";
  ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
  
}

void reset(uWS::WebSocket<uWS::SERVER> ws)
{
  string msg = "42[\"reset\",{}]";
  std::cout << msg << std::endl;
  ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
}

int main()
{
  uWS::Hub h;

  PID pid;
  /**
   * TODO: Initialize the pid variable.
   */
  //initializing the pid variables 
  // pid.Init(); //initial p values
  
  // Twiddle t(pid);

  double total_error = 0.0;
  int timesteps = 0;
  
  h.onMessage([&pid,&timesteps,&total_error](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, 
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event

    if (length && length > 2 && data[0] == '4' && data[1] == '2')
    {
      auto s = hasData(string(data).substr(0, length));

      if (s != "")
      {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry")
        {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());
          double speed = std::stod(j[1]["speed"].get<string>());
          double angle = std::stod(j[1]["steering_angle"].get<string>());
          /**
           * TODO: Calculate steering value here, remember the steering value is
           *   [-1, 1].
           * NOTE: Feel free to play around with the throttle and speed.
           *   Maybe use another PID controller to control the speed!
           */
          // std::cout<<timesteps<<std::endl;
          run_car(ws,pid,cte,angle); 
          if(pid.is_twiddle)
          {
            if(timesteps>=300 )
            {
              //then we update the parameters
              pid.Twiddle(total_error);
              reset(ws);
              timesteps = 0;
              total_error = 0.0;
            }
            else
            {
              total_error+=pow(cte,2);
              timesteps+=1;
            } //end of check if 
          } //end of twiddle if
        }  // end "telemetry" if
      else 
      {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }
  }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
};