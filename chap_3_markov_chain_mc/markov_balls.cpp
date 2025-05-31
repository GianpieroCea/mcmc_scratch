#include <random>
#include <time.h>
#include <array>
#include <iostream>
using std::array;
using std::endl; 
using std::cout;


/*Playing around with the concept of a Markov chain*/

/*in a markov chain, P(x_{k+1}) depends only on P(x_k)
This is another example taken from the example in chapter 3.1, a urn extraction.
The idea: start with a urn with 5 red and 5 blue balls. Extract without replacing,
continue. This is a markov chain since all it matters for transitioning is the current 
state (r,b), the history of how we got there does not matter.*/


std::default_random_engine e;

constexpr int NUMBER_SAMPLES = 10;


int main(){
    // Taking this code from C, might not be the best way to seed with current time
    time_t a = time(NULL);
    e.seed((unsigned) a);
    double red_balls =  5.0;
    double blue_balls = 5.0;
    
    static std::discrete_distribution<int> d({red_balls,blue_balls}); // this will output two possible values 0,1
    array<float,NUMBER_SAMPLES> samples;

    float current_mean_translation = 0.0;
    for(int i = 0;i < NUMBER_SAMPLES; ++i){
        int x_i = d(e);
        if (x_i == 0) {
            red_balls--;
        }else{
            blue_balls--;
        }
        // very unoptimised way to do sampling without replacement!
        d = std::discrete_distribution<int>({red_balls,blue_balls});
        samples[i] = x_i;
        cout << "Sampled ball is: " << x_i << endl;
        cout << "In the urn we now have: \n 1. " << red_balls << " red balls \n 2. "<<blue_balls << " blue balls" << endl;
        
    }
    
    return 0;

}