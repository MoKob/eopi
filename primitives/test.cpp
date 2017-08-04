#include "bit_operations.hpp"
#include "math.hpp"

#include <bitset>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int main() {
    cout << "Reverse of: " << std::bitset<64>(1) << " is "
         << std::bitset<64>(eopi::bits::reverse(1)) << endl;
    cout << "Reverse of: " << std::bitset<64>(127) << " is "
         << std::bitset<64>(eopi::bits::reverse(127)) << endl;
    cout << "Reverse of: " << std::bitset<64>(1234567890) << " is "
         << std::bitset<64>(eopi::bits::reverse(1234567890)) << endl;
    cout << "Reverse of: " << std::bitset<64>(numeric_limits<uint64_t>::max())
         << " is " << std::bitset<64>(
                          eopi::bits::reverse(numeric_limits<uint64_t>::max()))
         << endl;

    uint64_t value = 1;
    auto swapped = eopi::bits::swap(value, 1, 0);
    cout << "Swapping 0,1 of\n\t" << std::bitset<64>(value) << "\n\t"
         << std::bitset<64>(swapped) << endl;

    cout << "Parity of: " << bitset<8>(1) << ": " << eopi::bits::parity(1)
         << endl;
    cout << "Parity of: " << bitset<8>(2) << ": " << eopi::bits::parity(2)
         << endl;
    cout << "Parity of: " << bitset<8>(3) << ": " << eopi::bits::parity(3)
         << endl;
    value = 1 | (1llu << 16) | (1llu << 32);
    cout << "Parity of: " << bitset<64>(value) << ": "
         << eopi::bits::parity(value) << endl;

    cout << "Closest to " << 7 << "(" << eopi::bits::weight(7) << " - "
         << std::bitset<8>(7) << ") is " << eopi::bits::nearest_same_weight(7)
         << "(" << std::bitset<8>(eopi::bits::nearest_same_weight(7))
         << ") which als has weight: "
         << eopi::bits::weight(eopi::bits::nearest_same_weight(7)) << endl;

    cout << "Multiply Bitwise: " << eopi::bits::multiply_bitwise(13, 42)
         << " Should be: " << 13 * 42 << std::endl;

    cout << "Divisin: " << 127 * 123456 << " by 127 "
         << eopi::bits::divide_without_operators(127 * 123456, 127) << endl;

    cout << "Power: " << setprecision(12) << eopi::bits::power(42.0,7) << " Should be 230539333248" << std::endl;
    return 0;
}
