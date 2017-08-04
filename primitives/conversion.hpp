#ifndef EOPI_PRIMITIVES_CONVERSION_HPP_
#define EOPI_PRIMITIVES_CONVERSION_HPP_

#include <cctype>
#include <cstdint>
#include <string>

namespace eopi {
namespace bits {

// convert a string given in base `a` into a string of base `b`. This only
// works, as long as the encoded integer in input fits a 64bit unsigned
inline std::string convert_base(std::string input, const std::uint32_t base,
                                const std::uint32_t out_base) {
    // we only handle bases between 2 and 16
    auto const invalid_base = [](auto base) { return base <= 1 || base > 16; };

    if (input.empty() || invalid_base(base) || invalid_base(out_base))
        throw("Invalid input");

    // nothing to do?
    if (base == out_base) return input;

    bool negative = input.front() == '-';
    std::string result = "";

    std::uint64_t remainder = 0;

    auto const to_digit = [](char c) {
        if (!std::isxdigit(c)) throw("Invalid digit in string");

        if (std::isdigit(c))
            return c - '0';
        else
            return std::tolower(c) - 'a';
    };

    // only loop over digits of the input
    std::uint64_t power = 1;
    for (auto itr = input.begin() + (negative ? 1 : 0); itr != input.end();
         ++itr) {
        remainder += power * to_digit(*itr);
        power *= base;
    }

    auto const as_digit = [](std::int32_t value) {
        return value < 10 ? '0' + value : 'A' + (value - 10);
    };

    while (remainder) {
        result.push_back(as_digit(remainder % out_base));
        remainder /= out_base;
    }

    // add sign, when nevessary
    if (negative) result.push_back('-');

    // finally reverse the result and return
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace bits
}  // namespace eopi

#endif  // EOPI_PRIMITIVES_CONVERSION_HPP_
