#include "LedStrip.hpp"

#include <stdlib.h>
#include <assert.h>
#include <wiringPi.h>
#include <time.h>


#define DATA    0
#define CLOCK   7
#define RED_LED 1
#define GREEN_LED     3


void LedStrip::init(){
    wiringPiSetup();

    pinMode(DATA, OUTPUT) ;
    pinMode(CLOCK, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
}

LedStrip::LedStrip(unsigned int length):
    length(length), parent(NULL){
        ledColor = (Color*) malloc(length * sizeof(*ledColor));
        for (unsigned int i=0; i< length; i++){
            ledColor[i] = Color();// set the first bit of each paquet.
        }
        setGlobalLight(5);
        show();
    }

unsigned int LedStrip::getLength()const{
    return length;
}

LedStrip::LedStrip(Color* tab, unsigned int length, LedStrip* parent):
    length(length),ledColor(tab),parent(parent){

    }

LedStrip LedStrip::subStrip(unsigned int start, unsigned int end){
    return LedStrip(ledColor+start,end-start,this);
}

void LedStrip::setColor(unsigned int pos, Color color){
    digitalWrite(RED_LED,HIGH);

    struct timespec t;
    t.tv_sec=0;
    t.tv_nsec = 100000;//5000000;
    nanosleep(&t,NULL);

    assert(pos < length);
    ledColor[pos] = color;
    digitalWrite(RED_LED,LOW);
}

void LedStrip::fill(Color color){
    for (unsigned int pos=0; pos < length; pos++){
        ledColor[pos]=color;
    }
}

void LedStrip::show() const{
    if (parent){
        parent->show();
        return;
    }

    digitalWrite(GREEN_LED,HIGH);
    struct timespec t;
    t.tv_sec=0;
    t.tv_nsec = 1000;

    digitalWrite(CLOCK,0);
    digitalWrite(DATA,0);
    for (int i = 0; i < 32; i++){
        digitalWrite(CLOCK,0);
        digitalWrite(DATA,0);
        nanosleep(&t,NULL);
        digitalWrite(CLOCK,1);
    }
    for (unsigned int pos = 0; pos < length; pos++){
        uint16_t value = ledColor[pos].getValue();
        for (int i = 0; i <16; i++){
            digitalWrite(CLOCK, 0);
            digitalWrite(DATA,value & mask[i]);
            nanosleep(&t,NULL);
            digitalWrite(CLOCK, 1);
        }
    }

        digitalWrite(GREEN_LED,LOW);
}

void LedStrip::setGlobalLight(char level){
    uint16_t *new_mask;
    static uint16_t default_mask[16]={0x8000,
        0x4000,0x2000,0x1000,0x0800,0x0400,
        0x0200,0x0100,0x0080,0x0040,0x0020,
        0x0010,0x0008,0x0004,0x0002,0x0001};
    static uint16_t mask_0[16] = {0x8000,
        0,0,0,0,0,
        0,0,0,0,0,
        0,0,0,0,0};
    static uint16_t mask_1[16] = {0x8000,
        0,0,0,0,0x4000,
        0,0,0,0,0x0200,
        0,0,0,0,0x0010};
    static uint16_t mask_2[16] = {0x8000,
        0,0,0,0x4000,0x2000,
        0,0,0,0x0200,0x0100,
        0,0,0,0x0010,0x0008};
    static uint16_t mask_3[16] = {0x8000,
        0,0,0x4000,0x2000,0x1000,
        0,0,0x0200,0x0100,0x0080,
        0,0,0x0010,0x0008,0x0004};
    static uint16_t mask_4[16] = {0x8000,
        0,0x4000,0x2000,0x1000,0x0800,
        0,0x0200,0x0100,0x0080,0x0040,
        0,0x0010,0x0008,0x0004,0x0002};
    switch (level){
        case 0 :
            new_mask = mask_0;
            break;
        case 1 :
            new_mask=mask_1;
            break;
        case 2 :
            new_mask=mask_2;
            break;
        case 3 :
            new_mask=mask_3;
            break;
        case 4 :
            new_mask=mask_4;
            break;
        default :
            new_mask=default_mask;
    }
    for (int i=0; i< 16; i++){
        mask[i]=new_mask[i];
    }

}
