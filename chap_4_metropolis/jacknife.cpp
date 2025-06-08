/* Jacknife Method */


/* By definition MCMC methofd will prodcuce autocorrelated samples.
Ideally we want to get rid of this autocorrelation by discarding some samples
and only keep uncorrelated ones. 
A way of estimating autocorrelation length and statistical error is to use the
Jacknife method*/


#include <random>
#include <time.h>
#include <array>
#include <iostream>
#include <algorithm>
#include <cmath>
using std::array;
using std::endl; 
using std::cout;
using std::min;
using std::vector;
using std::pow;

/* Action S(x) -in this case a Gaussian*/
double action(double x ){
    return 0.5*x*x;
}

int main(){
    std::default_random_engine e;
    const int UNIFORM_C = 3;
    const int N_SAMPLES = 10000;
    const int WINDOW_SIZE = 50; //size of window to take samples
    vector<double> jacknife_vector_averages;
    int last_group_idx = 10;

    std::uniform_real_distribution<> u(-UNIFORM_C,UNIFORM_C);
    std::uniform_real_distribution<> u_r(0,1); // we will use this to determine acceptance

    float current_value = 0;
    // Taking this code from C, might not be the best way to seed with current time
    time_t seed_time = time(NULL);
    e.seed((unsigned) seed_time);

    double avg = 0.0 ;// maintain the average over the whole sample

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

        // now maintain the statistics using Welford's Algorithm and also add to jacknife group
        // Welford's Algorithm
        double res = current_value;
        double err = res -avg;
        avg += (1.0/(i+1))*(err);

        vector<double> current_group;
        current_group.push_back(res);


        if ((i +1 ) % WINDOW_SIZE  == 0 ){
            //we have done a full group, coumpue average and reset
            double group_avg = 0.0;
            for(double x: current_group){
                group_avg += x;
            }

            group_avg /= current_group.size();
            jacknife_vector_averages.push_back(group_avg);
            current_group.clear();
        }



    }

    // now compute the Jacknife error \delta_w

    double SSE = 0.0;
    int n = jacknife_vector_averages.size();
    for (int i = 0; i < n;++i){
        SSE += pow((jacknife_vector_averages[i] - avg),2.0);
    }

    double delta_w = sqrt(1.0/(n*(n-1))*SSE);

    cout << "Using a window of size: " << WINDOW_SIZE << " for: " << N_SAMPLES << " samples returns a jacknife error of: " << delta_w << endl;


    return 0;
}