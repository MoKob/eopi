#ifndef EOPI_PRIMITIVES_DOORS_HPP_
#define EOPI_PRIMITIVES_DOORS_HPP_

#include <cstdint>
#include <iostream>

namespace eopi
{
    namespace primitives
    {
        // output the solution to the five-hundred doors problem
        inline void fivehundred_doors()
        {
            // 500 closed doors as input
            // x_i toggles every ith door, starting at i
            // Which doords are open after 500 people did this.

            // Solution requires an odd number of divisors.
            // For x, we have 1:x, d_i:x/d_i as pairs.
            // Only in case of x == sqrt(x), there is no second divisor to pair x with.
            // This makes the solution to the problem the set of squares less than 500
            for( std::uint32_t i = 1; i*i <= 500; ++i )
                std::cout << i*i << std::endl;
        }
    } // namespace primitives
} // namespace eopi


#endif // EOPI_PRIMITIVES_DOORS_HPP_
