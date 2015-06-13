#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <wiringPi.h>
#include <csignal>

#include <cstdio>
#include <iostream>
#include <time.h>
#include <sys/time.h>

#include "LedStrip.hpp"
#include "Color.hpp"
#include "Animation.hpp"
#include "animations/RainbowAnimation.hpp"

#define LEDS_NUMBER 49




bool mainLoopContinue = true;

void signalHandler_kill(int a){
    mainLoopContinue = false;
    printf("received sig %d\nwill stop after a time\n",a);
}



void *anim_rainbow(void* p_leds){
    int setSize=100;
    Color set[setSize];
    char r=31,g=0,b=0,status=-1;
    for (int i = 0; i< setSize;i++){
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
    LedStrip &leds = *((LedStrip*) p_leds);
    int startPos=0,currentPos;
    for (;;) {
        currentPos=startPos;
        for (unsigned int i = 0; i < leds.getLength(); i++) {
            leds.setColor(i, set[currentPos]);
            currentPos=(currentPos+1)%setSize;
        }
        //leds.show();
        delay(100);
        startPos=(startPos+1)%setSize;
    }
}

void *anim_cursor(void* p_leds){
    Color color1,color2;
    LedStrip &leds = *((LedStrip*) p_leds);
    color1.setColor(16,31,16);
    color2.setColor(31,16,16);
    int r1d=1,g2d=1;
    unsigned int cur = 0;
    int side=1;//1 or -1
    for (;;) {
        delay(100);
        for (unsigned int i = 0; i < cur; i++) {
            leds.setColor(i, color1);
        }
        for (unsigned int i = cur; i < leds.getLength(); i++) {
            leds.setColor(i, color2);
        }
        //leds.show();
        cur += side;
        if (cur >= leds.getLength()){
            cur = leds.getLength()-1;
            side = -2;
            char r,g,b;
            color2.getRGB(r,g,b);
            r+=r1d;
            color2.setColor(r,g,b);
            if (r==31){
                r1d=-1;
            }else if (r==0){
                r1d=1;
            }
        }
        if (cur <= 0){
            cur = 0;
            side = 1;
            char r,g,b;
            color1.getRGB(r,g,b);
            g+=g2d;
            color1.setColor(r,g,b);
            if (g==31){
                g2d=-1;
            }else if (g==0){
                g2d=1;
            }
        }

    }
}

void * nothing(void*){
    return NULL;
}

int main(void){
    signal(SIGINT, signalHandler_kill);
    //ThreadedAnimation ta;

    LedStrip::init();
    LedStrip leds(LEDS_NUMBER);
    LedStrip ledSide = leds.subStrip(0,18);
    LedStrip ledTop = leds.subStrip(18,49);
    Color blanc;
    blanc.setColor(31,16,4);
    leds.setGlobalLight(5);

 //   pthread_t thread_top;
 //   pthread_t thread_side;
 //   if (pthread_create(&thread_top, NULL, anim_rainbow, (void*) &ledTop)==-1){
 //       perror("pthread_create");
 //       return EXIT_FAILURE;
 //   }
 //   if (pthread_create(&thread_side, NULL, nothing, (void*) &ledSide)==-1){
 //       perror("pthread_create");
 //       return EXIT_FAILURE;
 //   }
    
    ledSide.fill(Color(8,4,2));
    leds.setGlobalLight(4);

    RainbowAnimation rainbow;
    rainbow.setStrip(&leds);

while(mainLoopContinue){
    //ledSide.fill(Color(31,0,0));
    leds.show();
    delay(40);
    //ledSide.fill(Color(8,4,2));
    leds.show();
    delay(40);
}

//sleep(600);

    //ledSide.fill(Color(8,4,2));
    //ledTop.show();
    sleep(1);
    leds.setGlobalLight(4);
    leds.show();
    sleep(1);
    leds.setGlobalLight(3);
    leds.show();
    sleep(1);
    leds.setGlobalLight(2);
    leds.show();
    sleep(1);
    leds.setGlobalLight(1);
    leds.show();
    sleep(1);
    leds.setGlobalLight(0);
    leds.show();
    leds.fill(Color(0,0,0));
    leds.show();
    



    //pthread_join(thread_side,NULL);
    //pthread_join(thread_top,NULL);
    return 0;
}
