#include "DropAnimation.hpp"
#include <iostream>

#define DROP_RES ((int)15)
#define DROP_LEN ((int) DROP_RES * 5)


void DropAnimation::doAnimationStep(){
    for (unsigned int i = 0; i < leds->getLength(); i++) {
        char r_b,g_b,b_b;
        char r_d,g_d,b_d;
        background.getRGB(r_b, g_b, b_b);
        dropColor.getRGB(r_d, g_d, b_d);
        int relativePos = currentPos - DROP_RES*i;
        if (relativePos >= 0 && relativePos < DROP_LEN){
            int r = (r_b*relativePos + r_d * (DROP_LEN-relativePos))/DROP_LEN;
            int g = (g_b*relativePos + g_d * (DROP_LEN-relativePos))/DROP_LEN;
            int b = (b_b*relativePos + b_d * (DROP_LEN-relativePos))/DROP_LEN;
            leds->setColor(i, Color(r,g,b));
        }else{
            leds->setColor(i, background);
        }
    }
    currentPos+=speed;
    speed+=2;
    if (currentPos > 20*DROP_RES){
        currentPos = 0;
        speed = 0;
    }
}

DropAnimation::DropAnimation():Animation(true,30){
    background=Color(0,0,0);
    dropColor=Color(0,31,0);
    currentPos=0;
    speed=0;
}


