#ifndef NETWORK_ANIMATION_HPP
#define NETWORK_ANIMATION_HPP

#include "../Animation.hpp"

class NetworkAnimation : public Animation{
    int sock;

    static void mainThread(Animation* a);
    
    public :
        NetworkAnimation();

    virtual void doAnimationStep();
};

#endif
