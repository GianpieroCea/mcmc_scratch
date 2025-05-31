/* monte-carlo integral using the box muller */
#include <random>
#include <numbers>
#include <iostream>

std::default_random_engine e;
std::uniform_real_distribution<double> u(0.0,1.0);

int main(){
    double mean = 0;
    double var = 0;
    for(int i=0;i<10000;++i){
        // first sample two integers:
        double p = u(e);
        double q = u(e);
        
        // then apply box-muller transform
        double x = sin(std::numbers::pi*2*q)*sqrt(-2*log(p));
        double y = cos(std::numbers::pi*2*q)*sqrt(-2*log(p));

        // Welford's Algorithm
        double err = x -mean;
        mean += (1.0/(i+1))*(err);
        double err2 = x - mean;
        var += (err*err2)/(i+1.0);

    }
    std::cout << "avg is: " << mean << " and var is : " << var << std::endl;
    return 0;
    
}