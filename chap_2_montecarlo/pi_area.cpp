#include <time.h>
#include <iostream>
#include <random>

std::default_random_engine e;
std::uniform_real_distribution<double> u(0,1);

/* A basic monte-carlo approximation to pi: samples
a random pair (x,y) in the positive quadrant of the cartesian plane and
check whether the random pair is contained in the quarter of circle*/

int main(){
    int const N_ITER = 10000; // number of samples to use
    // Taking this code from C, might not be the best way to seed with current time
    time_t a = time(NULL);
    e.seed((unsigned) a);

    int n_in = 0;  // number of times the pair is in the circle

    for(int i =0;i < N_ITER;++i){
        double x = u(e);
        double y = u(e);
        // check if the sampled pair is in the circle:
    
        bool is_in_circle = x*x + y*y < 1e0;
    
        if (is_in_circle){
            ++n_in;
        }


        if(i % 100 == 0){
            std::cout << "The current sampled pair is: (" << x <<","<< y <<")" << std::endl;
            std::cout << "The current approximation to pi is" << ((double) n_in/N_ITER)*4 << std::endl;

        }
    
        
        
    }
    
    std::cout << "The final approximation to pi is: " << ((double) n_in/N_ITER)*4 << std::endl;
    
    return 0;

}