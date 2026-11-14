#pragma once
#include <iostream> 
#include <cstdlib>
#include <ctime>  
#include <cmath> 

// RANDOM 
namespace rd{
    void randseed(); 
    void randseed(int i); 
    int ransign();
    int randInt(int ub);
    int randInt();
    int randIntSign(int ub);
    float randsignf();
    float randf();
    float randfb(float upper_bound); 
    float randsignfb(float upper_bound); 
}
