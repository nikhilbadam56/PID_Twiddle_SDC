#include "PID.h"

/*
In this code we define the necessary things needed for implementing the twiddle algorithm
*/

class Twiddle
{
	public:
    	Twiddle(PID &pid);
        
        virtual ~Twiddle();
        
        //defining the necessary functions
        
        //basically we here do the state change of the twiddle algorithm , keep tracking of the number of iterations happened
        //keeping track of the best error . calculating the best error , totoal error,changing the parameters 
        
        bool is_used = false;
        
        bool initialization_phase = true;
        
//         PID pid;
        
        int state  = 0;
        
        double dist_count = 0;
        
        double error = 0;
        
        double total_error = 0;
        
        double best_count  = 0;
        
        double best_error = 0;
        
        void updateParameter(bool less_or_grt,PID &pid);
        
        int parameter_index = 0;
};