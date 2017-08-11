#ifndef EOPI_ARRAYS_PRIMES_HPP_
#define EOPI_ARRAYS_PRIMES_HPP_

#include <vector>
#include <cstdint>

namespace eopi {
namespace arrays {

std::vector<std::uint32_t> euler_sieve(std::uint32_t const max)
{
    std::vector<std::uint32_t> results;
    std::vector<bool> sieve(max+1,true);
    std::uint32_t i;
    for( i = 2; i*i <= max; ++i )
    {
        if( sieve[i] )
        {
            results.push_back(i);
            for( std::uint32_t k = i; k <= max; k+= i )
                sieve[k] = false;
        }
    }

    for( ; i <= max; ++i )
        if( sieve[i] )
            results.push_back(i);

    return results;
}

}  // namespace arrays
}  // namespace eopi

#endif  // EOPI_ARRAYS_PRIMES_HPP_
