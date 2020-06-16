#pragma once

/**
 * @brief This is a vector object. it is in rectangular form just
 * 
 */
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
    Vector(float x, float y, float z);

    /**
     * @brief Construct a new Vector object (copy constructor)
     * 
     * @param other this is another vector
     */
    Vector(const Vector &other);

    // sets the value of the vector
    void set(float x, float y, float z);

    // this has to be self explainatory
    float x, y, z;
};

