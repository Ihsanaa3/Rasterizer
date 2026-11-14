#include "extraFunctions.h"

//              RANDOM 

// sets a seed
void rd::randseed() { 
    std::srand(static_cast<unsigned int>(std::time(nullptr))); 
} 

void rd::randseed(int i){
    std::srand(i); 
}

// returns +1 or -1 
int rd::ransign(){
    int x = rand() % 2; 
    if (x == 0){
        return -1;
    } 
    return 1; 
}

int rd::randInt(int ub){
    return (rand() % (ub+1));
} 

int rd::randInt(){
    return rand();
}

// returns a random integer
int rd::randIntSign(int ub){
    int x = rand() % (ub+1); 
    return (x * ransign()); 
}

// returns a random float 
float rd::randsignf(){ 
    float x = static_cast <float> (rand())/static_cast <float> (RAND_MAX) ; 
    return (x * ransign()); 
}

// returns a random positive float
float rd::randf(){
    float x = static_cast<float>(rand())/ static_cast <float> (RAND_MAX); 
    return x; 
}

// returns a random positive float less than the upper bound
float rd::randfb(float upper_bound){
    float x = static_cast <float> (rand())/static_cast <float> (RAND_MAX/upper_bound) ; 
    return (x); 
}

// returns a random float less than the upper bound
float rd::randsignfb(float upper_bound){
    float x = static_cast <float> (rand())/static_cast <float> (RAND_MAX/upper_bound) ; 
    return (x * ransign()); 
}
