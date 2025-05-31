
#include <random>
#include <time.h>
#include <array>
#include <iostream>
using std::array;
using std::endl; 
using std::cout;
/*Rock paper scissors
A variation on the first setup where now they both use same strategy.

Procedure: 
A: repeats same move if she last won or draw, changes randomly if lost
B: repeats same move if she last won or draw, changes randomly if lost

this is :
- markov: each throw depednds only on prev launch for alice, indipended for b  so yes,
 - but it is neither irreducible not aperiodic -if they draw they stuck there forever*/

 int main(){
    std::default_random_engine e;
    std::uniform_int_distribution<> u(1,3); // 1:R,2:P,3:S
    // Taking this code from C, might not be the best way to seed with current time
    time_t seed_time = time(NULL);
    e.seed((unsigned) seed_time);

    const int N_THROWS = 10;
    static array<int,N_THROWS> history = array<int,N_THROWS>(); // will contain 1 for alice win, 0 draw, -1 loss

    int tot_a = 0; // initialise the total wins of Alice an bob
    int tot_b = 0;

    int a = -1; 
    int b = -1; // initialise current values for Alice an Bob to -1
    bool repeat_prev_a = false;
    bool repeat_prev_b = false;
    for(int i =0; i<N_THROWS; ++i){

  
        // we should refactor this with functions once we learn them properly!

        //alice throw - only sample new move when prev was unsuccesful
        if(not repeat_prev_a){

            a = u(e);
        }
        // bob throw - always 
        if(not repeat_prev_b){

            b = u(e);
        }

        if(a == b){
            //draw! (we increment both counters)
            repeat_prev_a = true; // note this is the case that will hinder aperiodicity and irreducibility 
            repeat_prev_b = true;
            history[i] = 0;
            ++tot_a;
            ++tot_b;

        }else if ((a== 1 and b== 3) or (a==2 and b==1) or (a ==3 and b== 2))
        {
            //alice win
            repeat_prev_a = true;
            repeat_prev_b = false;
            history[i] = 1;
            ++tot_a;
        }else{
            //alice lost
            repeat_prev_a = false;
            repeat_prev_b = true;
            history[i] = -1;
            ++tot_b;
            continue; 
        }
        

        

    }
    cout << "Total wins a: " << tot_a << endl;
    cout << "Total wins b: " << tot_b << endl;

    cout << "The history of wins was:"<< endl;
    for(int i = 0; i < N_THROWS; ++i){
        cout << " " << history[i] << " " << endl;
    }
    return 0;
 }