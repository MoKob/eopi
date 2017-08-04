#ifndef EOPI_PRIMITIVES_MATH_HPP_
#define EOPI_PRIMITIVES_MATH_HPP_

#include <cstdint>
#include <bitset>

#include "bit_operations.hpp"

namespace eopi {
namespace bits {

// unreasonable implementation of addition using a full adder for i1,i2,carry -> sum,carry
inline std::uint64_t add_bitwise(std::uint64_t lhs, std::uint64_t rhs) {
    std::uint32_t carry = 0;
    std::uint64_t result = 0;

    // add up all 64 bits
    for( std::uint32_t i = 0; i < 64; ++i, lhs >>= 1, rhs >>= 1 )
    {
        // pre-shift, so we can set the last bit within this loop
        result <<= 1;

        // get bits
        auto const lhs_bit = lhs & 1;
        auto const rhs_bit = rhs & 1;

        // compute the output bit
        auto const xor_lhs_rhs = lhs_bit ^ rhs_bit;
        result |= (xor_lhs_rhs ^ carry);

        // compute the out carry
        carry = (xor_lhs_rhs & carry) | (lhs_bit&rhs_bit);
    }

    return reverse(result);
}

// unreasonable implementation of multiplication without adding or multiply
inline std::uint64_t multiply_bitwise(std::uint64_t lhs, std::uint32_t rhs) {
    std::uint64_t result = 0;
    while(rhs)
    {
        if( rhs & 1 )
            result = add_bitwise(result,lhs);
        rhs >>= 1;
        lhs <<= 1;
    }
    return result;
}


// division (without remainder) using only shift/operator- and comparisons
inline std::uint64_t divide_without_operators(std::uint64_t dividend, std::uint64_t divisor)
{
    // ensure we will terminate
    if( divisor == 0 )
        throw("Invalid argument, dividing by zero");

    std::uint64_t divisor_times_2_n = divisor;
    std::uint32_t power = 1;
    // find the largest n so that 2^n * divisor < dividend
    while( divisor_times_2_n < dividend )
    {
        divisor_times_2_n <<= 1;
        power <<= 1;
    }

    std::uint64_t result = 0;
    while( dividend >= divisor )
    {
        if( divisor_times_2_n <= dividend )
        {
            result |= power;
            dividend -= divisor_times_2_n;
        }
        divisor_times_2_n >>=1;
        power >>= 1;
    }
    return result;
}

// compute the power of x via square and multiply
inline double power(double x, std::uint32_t power)
{
    double result = 1;

    // multiply the powers of two onto result
    // x x^2 x^4 ...
    // which represents the binary form of the power
    while(power)
    {
        if(power&1)
            result *= x;

        x = x*x;

        power>>=1;
    }
    return result;
}

}  // namespace bits
}  // namespace eopi

#endif  // EOPI_PRIMITIVES_MATH_HPP_
