#ifndef RAINBOW_ANIMATION_HPP
#define RAINBOW_ANIMATION_HPP

#include "../Animation.hpp"
#include "../Color.hpp"

#define SET_SIZE 100

class RainbowAnimation : public Animation{
    int currentPos,startPos;
    Color set[SET_SIZE];
    
virtual void doAnimationStep();

    public :
RainbowAnimation();
};


#endif
