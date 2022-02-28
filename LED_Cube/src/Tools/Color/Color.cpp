#include "Color.h"
// 3 color constructor
Color::Color(ui8 r, ui8 g, ui8 b)
{
    color = pk_color(r, g, b);
}

//takes a packed color
Color::Color(uint16_t color) : color(color) {}

// rgb are represeted by 255 - 0 scale, however the increments are not the same due to compression: Red as 5 bits, Green has 6 bits, and Blue has 5 bits.
ui8 Color::r()
{
    return (color & 0xF800) >> 8;
}
ui8 Color::g()
{
    return (color & 0x07E0) >> 3;
}
ui8 Color::b()
{
    return (color & 0x001F) << 3;
}

// so you can pass Colors as a uint16_t in function for ease of use
Color::operator uint16_t()
{
    return color;
}

// a very naive way to brighten colors, probably just needs to be re written with a better algo
Color &Color::operator++(int)
{
    if (rReal() == 0x001F || gReal() == 0x003F || bReal() == 0x001F)
    {
        return *this;
    }
    uint16_t next = rReal() * 1.5 + 0.5;
    rReal((next >= 32) ? 0x001F : next);
    next = gReal() * 1.5 + 0.5;
    gReal((next >= 64) ? 0x003F : next);
    next = bReal() * 1.5 + 0.5;
    bReal((next >= 32) ? 0x001F : next);
    return *this;
}

// very very naive way to darken colors. Will not work well with colors equaling zero
Color &Color::operator--(int)
{
    rReal(rReal() * 0.6666666 + 0.5);
    gReal(gReal() * 0.6666666 + 0.5);
    bReal(bReal() * 0.6666666 + 0.5);
    return *this;
}

// so you can write color = 0xFFFF; and it will work
Color &Color::operator=(uint16_t cIn)
{
    setColor(cIn);
    return *this;
}

// a set color function (kinda useless)
void Color::setColor(uint16_t cin)
{
    color = cin;
}

// gets the real values of the colors ie the bits that represent the colors in increments of 1
ui8 Color::rReal()
{
    return (color & 0xF800) >> 11;
}
ui8 Color::gReal()
{
    return (color & 0x07E0) >> 5;
}
ui8 Color::bReal()
{
    return (color & 0x001F);
}

// used to set the r g b values of the Color on a 255 - 0 scale
ui8 Color::r(uint16_t cIn)
{
    color = (color & 0x07FF) | ((cIn & ~0x0007) << 8);
}
ui8 Color::g(uint16_t cIn)
{
    color = (color & 0xF81F) | ((cIn & ~0x0003) << 3);
}
ui8 Color::b(uint16_t cIn)
{
    color = (color & 0xFFE0) | ((cIn & ~0x0007) >> 3);
}

// uses the real scale ie 5 bit red, 6 bit green, 5 bit blue
ui8 Color::rReal(uint16_t cIn)
{
    color = (color & 0x07FF) | ((cIn & ~0x00E0) << 11);
}
ui8 Color::gReal(uint16_t cIn)
{
    color = (color & 0xF81F) | ((cIn & ~0x00C0) << 5);
}
ui8 Color::bReal(uint16_t cIn)
{
    color = (color & 0xFFE0) | ((cIn & ~0x00E0));
}