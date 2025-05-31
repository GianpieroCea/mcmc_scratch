/* a continuation from the pi_area code where we analyse some stats
like error avg and std as sample increase */



#include <time.h>
#include <iostream>
#include <random>
#include <numbers>
#include <array>

std::default_random_engine e;
std::uniform_real_distribution<double> u(0,1);

/* A basic monte-carlo approximation to pi: samples
a random pair (x,y) in the positive quadrant of the cartesian plane and
check whether the random pair is contained in the quarter of circle*/


int main(){
    constexpr std::array<int,5> sample_sizes  = {10,100,1000,10000,100000};
    static std::array<double,5> averages = {0,0,0,0,0}; //will be used to storge the averages
    static std::array<double,5> stand_devs = {0,0,0,0,0}; // will be used to stored standard deviations
    int const N_EXPERIMENTS = 100; //how many experiments to run for each sample size

    // Taking this code from C, might not be the best way to seed with current time
    time_t a = time(NULL);
    e.seed((unsigned) a);

    //loop over samples sizes
    for(int i=0;i<5;++i){
        int const N_ITER = sample_sizes[i]; // number of samples to use
        std::cout << N_ITER << std::endl;

        double avg = 0; // initialise avg for this experiment
        double var = 0; // initialise var for this experiment
        
        //for a given sample repeat the experiment
        for (int n=0; n < N_EXPERIMENTS;++n){

            int n_in = 0;  // number of times the pair is in the circle

            // run the experiment by running monte-carlo simulations
            for(int j =0;j < N_ITER;++j){
                double x = u(e);
                double y = u(e);
                // check if the sampled pair is in the circle:
            
                bool is_in_circle = x*x + y*y < 1e0;
            
                if (is_in_circle){
                    ++n_in;
                }
            }
            double res = ((double) n_in/N_ITER)*4 ;

            // Welford's Algorithm
            double err = res -avg;
            avg += (1/(n+1))*(err);
            double err2 = res - avg;
            var += (err*err2)/(n+1);

 
        }
        averages[i] = avg;
        stand_devs[i] = var;

        std::cout << "For experiment where n_iter: " << N_ITER << "the average is: " << avg 
        << " and the variance is: " << var << std::endl;
    }

    
    
    
    return 0;

}