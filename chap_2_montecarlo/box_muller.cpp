/* simple implementation of box muller method to generate gaussian random numbers*/
#include <random>
#include <numbers>
#include <iostream>

std::default_random_engine e;
std::uniform_real_distribution<float> u(0,1);

int main(){
    for(int i=0;i<10000;++i){
        // first sample two integers:
        float p = u(e);
        float q = u(e);
        
        // then apply box-muller transform
        double x = sin(std::numbers::pi*2*q)*sqrt(-2*log(p));
        double y = cos(std::numbers::pi*2*q)*sqrt(-2*log(p));

        if(i % 10 == 0){
            std::cout << "the sampled gaussian values are: " << x << " and : " << y << std::endl;

        }
    }
    return 0;
    
}