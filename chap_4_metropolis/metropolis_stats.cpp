#include <random>
#include <time.h>
#include <array>
#include <iostream>
#include <fstream>
#include <algorithm>
using std::array;
using std::endl; 
using std::cout;
using std::min;
/*Metropolis algorithm*/

/* This is the basic method that is at the core of many mcmc methods*/

/* Action S(x) -in this case a Gaussian*/
double action(double x ){
    return 0.5*x*x;
}

int main(){
    std::default_random_engine e;
    const int UNIFORM_C = 1.5;
    const int N_SAMPLES = 50000;
    std::uniform_real_distribution<> u(-UNIFORM_C,UNIFORM_C);
    std::uniform_real_distribution<> u_r(0,1); // we will use this to determine acceptance

    double current_value = 100.0; // you  can also play with changing this and see "thermalization" happening
    // Taking this code from C, might not be the best way to seed with current time
    time_t seed_time = time(NULL);
    e.seed((unsigned) seed_time);

    double avg = 0.0; // initialise avg for this experiment
    double SSE = 0.0; // initialise SSE for this experiment


    std::ofstream f;
    f.open("metropolis_samples.csv");
    f << "sample";
        

    for(int i = 0; i < N_SAMPLES; ++i){

        // 1. choose a \delta_x in u(-c,c)
        double delta_x = u(e);
 
        // 2. propose a new value
        double proposed_new_value = current_value + delta_x;
 
        // 3. determine whether to accept or not
        double action_diff = action(current_value) - action(proposed_new_value);
        double acceptance_ratio = min(1.0,exp(action_diff));

        double r = u_r(e);

        if( r < acceptance_ratio ){
            // accept
            current_value = proposed_new_value;
        }



         // now maintain the statistics using Welford's Algorithm

        double res = current_value;

        // Welford's Algorithm
        double err = res -avg;
        avg += (1.0/(i+1))*(err);
        double err2 = res - avg;
        SSE += (err*err2);
        
        
        if( i % 100 == 0){
            cout << "Current avg is: " << avg << endl;
            cout << "Current var is: " << SSE/(i+1) << endl;
        }

        // we also save all sample to csv so that we can futher analyse it

        f << current_value << "\n" ;
    }

    // we close the file stream
    f.close();
    return 0;
}