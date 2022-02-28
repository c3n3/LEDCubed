#include "../../LED_Cube_library/types.h"
#include "../../Tools/Color/Color.h"
#include "../../Tools/ParticleSystem/Particle.h"
class Object
{
private:
    // function that draws the object
    void (*drawSelf)(ui8 x, ui8 y, ui8 z, Relativistic::Directions d, Color color);
public:
    // the direction that the object lives in
    Relativistic::Directions direction;
    Particle position;
    Color color;
    Object(Particle position, directRelativistic::Directionsions direction, void (*drawSelf)(ui8 x, ui8 y, ui8 z, Relativistic::Directions d, Color color), Color color = 0xFFFF): drawSelf(drawSelf), direction(direction), position(position), Color(color) {}
    void draw() {
        (*drawSelf)(position.point.x, position.point.y, position.point.z, color);
    }
};
