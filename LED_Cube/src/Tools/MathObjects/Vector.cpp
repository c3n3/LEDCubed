#include "Vector.h"
void Vector::set(float a,float b, float c) {x = a; y = b; z = c;};
Vector::Vector(float a, float b, float c) {set(a,b,c);};
Vector::Vector() {x = 0; y = 0; z = 0;};
Vector::Vector (const Vector& other) {
    x = other.x;
    y = other.y;
    z = other.z;
};