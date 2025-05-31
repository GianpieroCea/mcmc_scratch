#include <random>
#include <time.h>
#include <array>
#include <iostream>
using std::array;
using std::endl; 
using std::cout;


/*Playing around with the concept of a Markov chain*/

/*in a markov chain, P(x_{k+1}) depends only on P(x_k)
 Let's define a simple probabilistic markov chain of 1-dimension
 for instance, we can start with a normal gaussain N(0,1). Then next
 value we sample from gaussain with 1 variance centered at the new place and so on*/


 std::default_random_engine e;
 std::normal_distribution<float> N(0,1);

 constexpr int NUMBER_SAMPLES = 100;


int main(){
    // Taking this code from C, might not be the best way to seed with current time
    time_t a = time(NULL);
    e.seed((unsigned) a);

    array<float,NUMBER_SAMPLES> samples;

    float current_mean_translation = 0.0;
    for(int i = 0;i < NUMBER_SAMPLES; ++i){
        float x_i = N(e) + current_mean_translation;
        samples[i] = x_i;
        current_mean_translation = x_i;
        cout << "Sample num: " << i << " is: " << x_i << endl;
        
    }
    
    return 0;

}