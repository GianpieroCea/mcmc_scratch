#include <random>
#include <time.h>
#include <array>
#include <iostream>
#include <algorithm>
using std::array;
using std::endl; 
using std::cout;
using std::min;
/*Metropolis algorithm*/

/* This is the basic method that is at the core of many mcmc methods.
In this code we examine a bit the relationship between  different acceptance rates.*/

/* Action S(x) -in this case a Gaussian*/
double action(double x ){
    return 0.5*x*x;
}

int main(){
    std::default_random_engine e;
    const int UNIFORM_C = 3;
    const int N_SAMPLES = 100;

    std::array
    std::uniform_real_distribution<> u(-UNIFORM_C,UNIFORM_C);
    std::uniform_real_distribution<> u_r(0,1); // we will use this to determine acceptance

    float current_value = 0;
    // Taking this code from C, might not be the best way to seed with current time
    time_t seed_time = time(NULL);
    e.seed((unsigned) seed_time);

    for(int i = 0; i < N_SAMPLES; ++i){
        cout << "################################"<< endl;
        cout << "Sample number: "<< i<< "\n"<< endl;
        cout << "Current value: "<< current_value<< "\n"<<endl;
        // 1. choose a \delta_x in u(-c,c)
        double delta_x = u(e);
        cout << "Sample delta: "<< delta_x<< "\n"<<endl;
        // 2. propose a new value
        double proposed_new_value = current_value + delta_x;
        cout << "Proposed new value: "<< proposed_new_value <<"\n"<<endl;
        // 3. determine whether to accept or not
        double action_diff = action(current_value) - action(proposed_new_value);
        double acceptance_ratio = min(1.0,exp(action_diff));
        cout << "Acceptance ratio: "<< acceptance_ratio <<"\n"<<endl;
        double r = u_r(e);
        cout << "Sampled r: "<< r <<"\n"<<endl;
        if( r < acceptance_ratio ){
            // accept
            cout << "Accepted!" << endl;
            current_value = proposed_new_value;
        }
    }
    return 0;
}