#include <random>
#include <time.h>
#include <array>
#include <iostream>
using std::array;
using std::endl; 
using std::cout;
/*Dice rolls


Procedure: keep throwing a dice and keep a tally.

this is :
- markov: each throw is independendt and the history does not matter,
 just the current sum
 -not irreducible: onlty grows, so cannot go back to beginning
 -not perioic: not even well defined*/

 int main(){
    std::default_random_engine e;
    std::uniform_int_distribution<> u(1,6);
    // Taking this code from C, might not be the best way to seed with current time
    time_t a = time(NULL);
    e.seed((unsigned) a);

    int sum = 0;

    for(int i =0; i<10; ++i){
        sum += u(e);
        cout << "Current tally: " << sum << endl;
    }
    return 0;
 }