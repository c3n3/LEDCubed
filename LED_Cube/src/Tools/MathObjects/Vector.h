#pragma once

/**
 * @brief This is a vector object. it is in rectangular form just
 * 
 */
template<typename T>
struct Vector
{
    /**
     * @brief Construct a new Vector object with 0,0,0 as initial values
     * 
     */
    Vector();

    /**
     * @brief Construct a new Vector object
     * 
     * @param x coord
     * @param y coord
     * @param z coord
     */
    Vector(T x, T y, T z);

    /**
     * @brief Construct a new Vector object (copy constructor)
     * 
     * @param other this is another vector
     */
    Vector(const Vector<T> &other);

    // sets the value of the vector
    void set(T x, T y, T z);

    // add two together
    void add(const Vector<T> other);

    // this has to be self explainatory
    T x, y, z;
};

