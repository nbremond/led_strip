#ifndef DROP_HPP
#define DROP_HPP

#include "../Animation.hpp"
#include "../Color.hpp"


class DropAnimation : public Animation{
    unsigned int currentPos;
    unsigned int speed;
    Color background, dropColor;

    virtual void doAnimationStep();

    public :
    DropAnimation();
};


#endif
