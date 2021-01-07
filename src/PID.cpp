#include "PID.h"
#include <iostream>



/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init() {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  p_error = 0;
  d_error = 0;
  i_error = 0;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */

  //derivative error   
  d_error = (cte - previous_error);
  
  //proportional p error
  p_error = cte;
  
  //integration error
  i_error = i_error+cte;
  
  previous_error = cte;

        
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */

double steer = (p[0]*p_error)+(p[1]*d_error)+(p[2]*i_error); //pdi
  if (steer > 1)
  {
    steer = 0.8;
  } 
  else if (steer < -1)
  {
    steer = -0.8;
  }
  return steer;
}

void PID::Twiddle(double total_error)
{
  //slightly different than the original twiddle algorithm
  //here we are tuning the concerned parameter so no need to maintain a separate index variable
  //but we have to change states accordingly
  double previous_parameter = parameter;
  // if(!is_initialized_twiddle)
  // {
  //   best_error_so_far = total_error;
  //   is_initialized_twiddle = true;
  //   std::cout<<"Twiddle Init Done----------------------------"<<std::endl;
  // }
   std::cout<<best_error_so_far<<"   "<<total_error<<std::endl;
   std::cout<<state<<std::endl;
    switch(state)
    {
      case 0:
      {
        best_error_so_far = total_error;
        p[parameter] += dp[parameter];
        state = 1;
        break;
      }
      case 1:
      {
        //after the above change if there is any change in the total error
        if(total_error<best_error_so_far)
        {
          std::cout<<"inside the state 1 true"<<std::endl;
          best_error_so_far = total_error;
          dp[parameter] *= 1.1;
          parameter = (parameter+1)%3;
          state=0;
        }
        else
        {
          std::cout<<"inside the state 1 else"<<std::endl;
          p[parameter]-=2*dp[parameter]; // change
          this->state=2;
          std::cout<<state<<std::endl;
        }        
        break;
      }
      case 2:
      {
        if(total_error<best_error_so_far)
        {
          std::cout<<"inside the state 2 true"<<std::endl;
          best_error_so_far = total_error;
          //this means that the  update worked so retain the parameter value
          dp[parameter] *=1.1;
          parameter = (parameter+1)%3;
        }
        else
        {
          std::cout<<"inside the state 2 false"<<std::endl;
            //either going up or going down worked here
            p[parameter]+=dp[parameter];
            dp[parameter]*=0.9;
            parameter = (parameter+1)%3;
        }
        state=0;
        break;
      }
    }
  std::cout<<"Iteration "<<iter<<"  Parameters"<<"\n"<<std::endl;
  std::cout<<"kp"<<"kd"<<"ki"<<std::endl;
  std::cout<<p[0]<<p[1]<<p[2]<<std::endl;

  std::cout<<"Best error"<<best_error_so_far<<std::endl;
  iter+=1;
}