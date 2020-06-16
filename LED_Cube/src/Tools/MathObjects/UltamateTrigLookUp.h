#pragma once
#include "../../LED_Cube_library/types.h"

/**
 * @brief This is an INTEGER sin lookup table that is generated on the basis of the template arguments. 
 * 
 * @tparam T this is the type of table. ONLY use integer types or else this will most likely fail miserably 
 * @tparam N This is the resolution of the table. This means the table goes from 0 to N in a sinusoidal fashion (table[i] = (N / 2.0) * sin(2 * pi * ((i * 1.0) / (N * 1.0))) + (N / 2.0) + 0.5))
 */
template <typename T, int N>
struct SinLookUpTable {
    T table[N];

    // gets the value as a range between 0 and N. 
    T operator[](T i) {
        i = i % N;
        return table[i];
    }

    /**
     * @brief Construct a new Sin Look Up Table object
     * 
     */
    SinLookUpTable() {
        double pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062; // that might be a bit long
        for (int i = 0; i < N; i++) {
            // this is just some math to make the table go from 0 - N in sinusoidal fashion
            table[i] = (T)((N / 2.0) * sin(2 * pi * ((i * 1.0) / (N * 1.0))) + (N / 2.0) + 0.5);
        }
    }

    // gets the actual sine value as a decimal from the table. NO promises that this is faster than just using sin() that testing has yet to be done
    float operator() (T i) {
        i = i % N;
        return (table[i] - N / 2.0f) / (N / 2.0f);
    }
};