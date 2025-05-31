#include <time.h>
#include <iostream>
#include <random>
#include <array>
#include <numbers>

/* a simple example of how naive monte carlo can fail!
if trying to compute gaussain and we naively sample at random,
most mass does not contribute to the integral!*/

std::default_random_engine e;


int main(){

    constexpr std::array<int,5> boundary = {2,10,100,1000};

    for(int i = 0; i<5; ++i){
        int a = boundary[i];
        std::uniform_real_distribution<double> u(-a,a);

        int const N_ITER = 100000
        ; // number of samples to use
        // Taking this code from C, might not be the best way to seed with current time
        time_t t = time(NULL);
        e.seed((unsigned) t);

        double sum_y = 0;  // the approximated integral

        for(int i =0;i < N_ITER;++i){
            double x = u(e);    
            double y = exp(-(x*x)/2)*(1/sqrt(2*std::numbers::pi));
        
            sum_y += y;

        
        }
    
        std::cout << "The final approximation is: " <<  ((double) sum_y/N_ITER)*2*a << std::endl;
    
    }


    
    
    
    return 0;

}