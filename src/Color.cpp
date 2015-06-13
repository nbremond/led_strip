#include "Color.hpp"

#include <assert.h>


#define COLOR_MASK 0x1F//five first bits
#define RED_MASK 0x03E0
#define GREEN_MASK 0x7C00
#define BLUE_MASK 0x001F
#define LONELY_BIT_MASK 0x8000

Color::Color(){
    value = LONELY_BIT_MASK;// set the first bit.
}

Color::Color(char red, char green, char blue){
    value = LONELY_BIT_MASK;// set the first bit.
    setColor(red,green,blue);
}

void Color::setColor(char red, char green, char blue){
    value &= LONELY_BIT_MASK;//keep only the first bit
    value |= (green & COLOR_MASK) << 10;
    value |= (red & COLOR_MASK) << 5;
    value |= (blue & COLOR_MASK);
}

void Color::getRGB(char& red, char& green, char & blue){
    red = (value & RED_MASK) >> 5;
    green = (value & GREEN_MASK) >> 10;
    blue = (value & BLUE_MASK);
}

uint16_t Color::getValue() const{
    return value;
}
