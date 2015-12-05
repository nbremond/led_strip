#ifndef LED_STRIP_HPP
#define LED_STRIP_HPP

#include <cstdint>

class LedStrip;

#include "Color.hpp"

class LedStrip{
    const unsigned int DATA;
    const unsigned int CLOCK;
    unsigned int length;
    Color *ledColor;
    LedStrip *parent; //NULL if the object is the main object.
    uint16_t mask[16];///<- the masks to export the bits.

    LedStrip(Color*tab, unsigned int length, LedStrip* parent);

    public :
    static void init();

    LedStrip(unsigned int dataPin, unsigned int clockPin, unsigned int length);
    unsigned int getLength() const;
    LedStrip subStrip(unsigned int start, unsigned int end);
    void setColor(unsigned int pos, Color color);
    void fill(Color color);
    void show() const;
    void setGlobalLight(char level);

};

#endif
