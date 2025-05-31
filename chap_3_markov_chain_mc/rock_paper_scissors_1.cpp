#include <random>
#include <time.h>
#include <array>
#include <iostream>
using std::array;
using std::endl; 
using std::cout;
/*Rock paper scissors


Procedure: 
A: repeats same move if she last won or draw, changes randomly if lost
B: always changes randomly

this is :
- markov: each throw depednds only on prev launch for alice, indipended for b  so yes,
 -not irreducible: here the space consists of the pair (i,j) with i \in 1,2,3. We see all 9 possibility can always be reached from
 any case thanks to the fact that b is always random so at some point alice will also change her move
 -not periodic: every possible length of perio is achievable*/

 int main(){
    std::default_random_engine e;
    std::uniform_int_distribution<> u(1,3); // 1:R,2:P,3:S
    // Taking this code from C, might not be the best way to seed with current time
    time_t seed_time = time(NULL);
    e.seed((unsigned) seed_time);
    const int N_THROWS = 10;

    int tot_a, tot_b; // initialise the total wins of Alice an bob
    int a = -1; 
    int b = -1; // initialise current values for Alice an Bob to -1
    bool repeat_prev = false;
    for(int i =0; i<N_THROWS; ++i){

        // we should refactor this with functions once we learn them properly!

        //alice throw - only sample new move when prev was unsuccesful
        if(not repeat_prev){

            a = u(e);
        }
        // bob throw - always random
        b = u(e);

        if(a == b){
            //draw! (we increment both counters)
            ++tot_a;
            ++tot_b;
            repeat_prev = true;

        }else if ((a== 1 and b== 3) or (a==2 and b==1) or (a ==3 and b== 2))
        {
            //alice win
            repeat_prev = true;
            ++tot_a;
        }else{
            //alice lost
            ++tot_b;
            continue; // by default we do not repeat
        }
        

        

    }
    cout << "Total wins a: " << tot_a << endl;
    cout << "Total wins b: " << tot_b << endl;
    return 0;
 }