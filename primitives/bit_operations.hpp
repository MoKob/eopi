#include <bitset>
#include <cstdint>
#include <limits>

#include <iostream>

namespace eopi {
namespace bits {

// compile-time look-up table to compute the parity of a value
template <std::uint16_t SIZE>
struct ParityLookupTable {
    constexpr ParityLookupTable() {
        // divide and conquer (parity X = parity [0:7] ^ parity[8:15]
        auto const calculate_parity = [](std::uint16_t value) {
            value ^= value >> 8;
            value ^= value >> 4;
            value ^= value >> 2;
            value ^= value >> 1;
            return (value & 1) == 1;
        };
        for (std::uint16_t i = 0; i < SIZE; ++i) {
            parity[i] = calculate_parity(i);
        }
    }

    std::bitset<SIZE> parity;
};

// storing the reversed bits of 16 bit integers
struct ReverseLookupTable {
    constexpr ReverseLookupTable() : reversed()
    {
        for (std::uint16_t i = 0; i < std::numeric_limits<std::uint16_t>::max(); ++i)
        {
            auto value = i;
            reversed[i] = 0;
            for (int bit = 0; bit < 15; ++bit) {
                reversed[i] |= value & 1;
                reversed[i] <<= 1;
                value >>= 1;
            }
            reversed[i] |= value & 1;
        }
        reversed[std::numeric_limits<std::uint16_t>::max()] = std::numeric_limits<std::uint16_t>::max();
    }

    std::uint16_t reversed[std::numeric_limits<std::uint16_t>::max()+1];
};

// compute parity in chunks of four precomputed values
inline bool parity(std::uint64_t value) {
    auto const constexpr mask = std::numeric_limits<std::uint16_t>::max();
    static const ParityLookupTable<mask> lookup;
    bool result = lookup.parity[value & mask];
    value >>= 16;
    result = result ^ lookup.parity[value & mask];
    value >>= 16;
    result = result ^ lookup.parity[value & mask];
    value >>= 16;
    return result ^ lookup.parity[value];
}

// swapping bits is only necessary if the two bits actually differ. In the case
// they differ, flipping bits can be achieved via xor with the respective bits
// set to 1. 0000 ^ 0110 = 0110 , 1010 ^ 0110 = 1100
inline std::uint64_t swap(std::uint64_t value, std::uint32_t i,
                          std::uint32_t j) {
    if ((value & (1 << i)) != (value & (1 << j))) value ^= (1 << i) | (1 << j);

    return value;
}

inline std::uint64_t reverse(std::uint64_t value) {
    auto const constexpr mask = std::numeric_limits<std::uint16_t>::max();
    static const ReverseLookupTable lookup;
    std::uint64_t result = 0;
    for (int i = 0; i < 3; ++i) {
        result |= lookup.reversed[value & mask];
        result <<= 16;
        value >>= 16;
    }
    result |= lookup.reversed[value];
    return result;
}

}  // namespace bits
}  // namespace eopi
