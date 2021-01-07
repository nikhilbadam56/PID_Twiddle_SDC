#include "Twiddle.h"
#include "PID.h"
#include <iostream>

Twiddle::Twiddle(PID &pid)
{
//   this->pid = pid; //taking the reference of the pid class for updating or accessing the p and dp values
  
};


Twiddle::~Twiddle() {};

//defining the functions in the twiddle.h file

void Twiddle::updateParameter(bool less_or_grt,PID &pid)
{
  //we change the staet and also update the parameters over here
  std::cout<<"[----------] update parameter"<<pid.p[0]<<"---"<<pid.p[1]<<"---"<<pid.p[2]<<std::endl;
  std::cout<<"[----------] update parameter difference"<<pid.dp[0]<<"---"<<pid.dp[1]<<"---"<<pid.dp[2]<<std::endl;
  if(less_or_grt)
  {
    //if true this measn whatever the previous state and corresponding update it showed better result so we retain the change and update next parameter
    switch(state)
    {
      case 0:
        //if the good result is obtained being in the 0 state
        //then we change the parameter index and go to state 1
        state  = 1;
        break;
      case 1:
        pid.dp[parameter_index] *= 1.1;
        parameter_index = (parameter_index+1)%3;
        pid.p[parameter_index]+=pid.dp[parameter_index];
        state  = 1;
        break;
      case 2:
        pid.dp[parameter_index] *=1.1;
        parameter_index  = (parameter_index+1)%3;
        pid.p[parameter_index] += pid.dp[parameter_index];
        state = 1;
        break;
    }
    
  }
  else
  {
    switch(state)
    {
      case 0:
        // if last state we were in is 0 and it didnot improve the results
        pid.p[parameter_index] += pid.dp[parameter_index];        
		state  = 1;
        break;
      case 1:

        pid.p[parameter_index] -= 2 * pid.dp[parameter_index];
        state  = 2;
        break;
      case 2:
        pid.p[parameter_index] += pid.dp[parameter_index];
        pid.dp[parameter_index] *= 0.9;
        parameter_index = (parameter_index + 1) % 3;
        pid.p[parameter_index] += pid.dp[parameter_index];
        state = 1;
        break;
    }
    
  }
}
