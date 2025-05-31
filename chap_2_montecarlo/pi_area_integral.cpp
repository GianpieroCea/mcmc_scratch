#include <time.h>
#include <iostream>
#include <random>

std::default_random_engine e;
std::uniform_real_distribution<double> u(0,1);

/* A basic monte-carlo approximation to pi,
this time using the integral of a curve*/

int main(){
    int const N_ITER = 10000; // number of samples to use
    // Taking this code from C, might not be the best way to seed with current time
    time_t a = time(NULL);
    e.seed((unsigned) a);

    double sum_y = 0;  // the approximated integral

    for(int i =0;i < N_ITER;++i){
        double x = u(e);    
        double y = sqrt(1e0-x*x);
    
        sum_y += y;


        if(i % 100 == 0){
            std::cout << "The current sampled pair is: (" << x <<","<< y <<")" << std::endl;
            std::cout << "The current approximation to pi is " << ((double) sum_y/i)*4 << std::endl;

        }
    
        
        
    }
    
    std::cout << "The final approximation to pi is: " << ((double) sum_y/N_ITER)*4 << std::endl;
    
    return 0;

}