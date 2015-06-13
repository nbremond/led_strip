#ifndef COLOR_HPP
#define COLOR_HPP

#include <cstdint>

class Color{
    uint16_t value;
    public :
    Color();
    Color(char red, char green, char blue);
    void setColor(char red,char green, char blue);
    void getRGB(char& red, char& green, char& blue);
    uint16_t getValue() const;
};

#endif
