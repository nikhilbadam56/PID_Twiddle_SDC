#include<vector>
#ifndef PID_H
#define PID_H

class PID {
 public:
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init();

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);
  
  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();

  void Twiddle(double total_error); //this function takes in the the parameter to be tuned and also the accumulated error
  
  
  std::vector<double> dp {1,1,1};
  //p component along with D component 
  //results in a smooth function overall
  //a small value to the i component decreases the steady state error.

  std::vector<double> p {0.084,2.4,0.0005}; //pdi  
  double previous_error = 0;

  bool is_twiddle  = false;
  bool is_initialized_twiddle = false;
  int state = 0;
  bool is_set = false;
  double best_error_so_far;
  double iter = 0;
  int parameter = 0;
  
 private:
  /**
   * PID Errors
   */
  double p_error = 0;
  double i_error = 0;
  double d_error = 0;
};

#endif  // PID_H