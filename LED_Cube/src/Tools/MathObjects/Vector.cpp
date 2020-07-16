#include "Vector.h"
template<typename T>
void Vector<T>::set(T a, T b, T c) {x = a; y = b; z = c;}

template<typename T>
Vector<T>::Vector(T a, T b, T c) {
    x = a; y = b; z = c;
}

template<typename T>
Vector<T>::Vector() {x = 0; y = 0; z = 0;}

template<typename T>
Vector<T>::Vector (const Vector<T>& other) {
    x = other.x;
    y = other.y;
    z = other.z;
}

template<typename T>
void Vector<T>::add(const Vector<T> other) {
    x = x + other.x;
    y = y + other.y;
    z = z + other.z;
}

template class Vector<float>;
template class Vector<unsigned char>;
