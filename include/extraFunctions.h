#pragma once
#include <iostream> 
#include <cstdlib>
#include <ctime>  
#include <cmath> 

// RANDOM 
namespace rd{
    void randseed(); 
    void setseed(int i); 
    int ransign();
    int randIntSign(int ub);
    float randsignf();
    float randf();
    float randfb(float upper_bound); 
    float randsignfb(float upper_bound); 
}
