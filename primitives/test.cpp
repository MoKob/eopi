#include "bit_operations.hpp"
#include "conversion.hpp"
#include "geometry.hpp"
#include "math.hpp"
#include "doors.hpp"

#include <bitset>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

int main() {
    cout << "Reverse of: " << std::bitset<64>(1) << " is "
         << std::bitset<64>(eopi::primitives::reverse(1)) << endl;
    cout << "Reverse of: " << std::bitset<64>(127) << " is "
         << std::bitset<64>(eopi::primitives::reverse(127)) << endl;
    cout << "Reverse of: " << std::bitset<64>(1234567890) << " is "
         << std::bitset<64>(eopi::primitives::reverse(1234567890)) << endl;
    cout << "Reverse of: " << std::bitset<64>(numeric_limits<uint64_t>::max())
         << " is " << std::bitset<64>(eopi::primitives::reverse(
                          numeric_limits<uint64_t>::max()))
         << endl;

    uint64_t value = 1;
    auto swapped = eopi::primitives::swap(value, 1, 0);
    cout << "Swapping 0,1 of\n\t" << std::bitset<64>(value) << "\n\t"
         << std::bitset<64>(swapped) << endl;

    cout << "Parity of: " << bitset<8>(1) << ": " << eopi::primitives::parity(1)
         << endl;
    cout << "Parity of: " << bitset<8>(2) << ": " << eopi::primitives::parity(2)
         << endl;
    cout << "Parity of: " << bitset<8>(3) << ": " << eopi::primitives::parity(3)
         << endl;
    value = 1 | (1llu << 16) | (1llu << 32);
    cout << "Parity of: " << bitset<64>(value) << ": "
         << eopi::primitives::parity(value) << endl;

    cout << "Closest to " << 7 << "(" << eopi::primitives::weight(7) << " - "
         << std::bitset<8>(7) << ") is "
         << eopi::primitives::nearest_same_weight(7) << "("
         << std::bitset<8>(eopi::primitives::nearest_same_weight(7))
         << ") which als has weight: "
         << eopi::primitives::weight(eopi::primitives::nearest_same_weight(7))
         << endl;

    cout << "Multiply Bitwise: " << eopi::primitives::multiply_bitwise(13, 42)
         << " Should be: " << 13 * 42 << std::endl;

    cout << "Divisin: " << 127 * 123456 << " by 127 "
         << eopi::primitives::divide_without_operators(127 * 123456, 127)
         << endl;

    cout << "Power: " << setprecision(12) << eopi::primitives::power(42.0, 7)
         << " Should be 230539333248" << std::endl;

    auto val = eopi::primitives::convert_base("1011101", 2, 10);
    cout << "Binary: 1011101 equals: " << val << std::endl;

    cout << "Spreadsheet: A: " << eopi::primitives::spreadsheet_encoding("A")
         << " AA: " << eopi::primitives::spreadsheet_encoding("AA")
         << " Z: " << eopi::primitives::spreadsheet_encoding("Z")
         << " AZ: " << eopi::primitives::spreadsheet_encoding("AZ") << endl;
    cout << "Reverse 12345678: " << eopi::primitives::reverse_digits(12345678)
         << std::endl;

    cout << "Palindromes: " << eopi::primitives::is_palindrome(111) << " (111) "
         << eopi::primitives::is_palindrome(122) << " (122) "
         << eopi::primitives::is_palindrome(121121) << " (121121)"
         << eopi::primitives::is_palindrome(7) << " (7)" << endl;

    std::srand(time(NULL));
    cout << "Rng (2-5): " << eopi::primitives::rng_coin(2, 5) << " "
         << eopi::primitives::rng_coin(2, 5) << " "
         << eopi::primitives::rng_coin(2, 5) << " "
         << eopi::primitives::rng_coin(2, 5) << " "
         << eopi::primitives::rng_coin(2, 5) << std::endl;

    eopi::primitives::Rectangle first{eopi::primitives::Point{0, 0},
                                      eopi::primitives::Point{3, 2}};
    eopi::primitives::Rectangle second{eopi::primitives::Point{1, 1},
                                       eopi::primitives::Point{2, 4}};

    cout << first << " and " << second
         << " intersect in: " << first.intersect(second) << endl;

    cout << "Open doors:\n";
    eopi::primitives::fivehundred_doors();
    return 0;
}
