#include "RainbowAnimation.hpp"

void RainbowAnimation::doAnimationStep(){
       currentPos=startPos;
        for (unsigned int i = 0; i < leds->getLength(); i++) {
            leds->setColor(i, set[currentPos]);
            currentPos=(currentPos+1)%SET_SIZE;
        }
        startPos=(startPos+1)%SET_SIZE;
}

RainbowAnimation::RainbowAnimation():Animation(true,25){
    char r=31,g=0,b=0,status=-1;
    for (int i = 0; i< SET_SIZE;i++){
        //printf("%d\t()%d)%d,%d,%d\n",i,status,r,g,b);
        set[i]= Color(r,g,b);
        if (!(i%31))
            status++;
        switch (status){
            case 0:
                r--;
                g++;
                break;
            case 1:
                g--;
                b++;
                break;
            case 2:
                b--;
                r++;
                break;
        }
    }
    startPos=0;
}
