#ifndef EOPI_STRINGS_HPP_
#define EOPI_STRINGS_HPP_

#include <algorithm>
#include <cmath>
#include <string>
#include <sstream>

namespace eopi {
namespace strings {

void remove_and_replace(std::size_t input_size, std::string& result) {
    // remove 'b's
    std::size_t output_pos = 0;
    for (std::size_t i = 0; i < input_size; ++i) {
        if (result[i] != 'b') result[output_pos++] = result[i];
    }
    input_size = output_pos;
    // look at the next char
    output_pos = result.size() - 1;
    while (input_size--) {
        if (result[input_size] == 'a') {
            // add to 'd's
            result[output_pos--] = 'd';
            result[output_pos--] = 'd';
        }
    }
}

// check whether a given string is a palindrome
bool is_palindrom(std::string const& str) {
    auto itr = str.begin();
    auto ritr = str.rbegin();
    for (std::size_t i = 0; 2 * i < str.size(); ++i, ++itr, ++ritr)
        if (*itr != *ritr) return false;
    return true;
}

std::string reverse_words(std::string sentence) {
    std::reverse(sentence.begin(), sentence.end());

    auto itr = sentence.begin();
    auto end = sentence.begin();
    while (end != sentence.end()) {
        end = std::find(itr, sentence.end(), ' ');
        std::reverse(itr, end);
        itr = end == sentence.end() ? end : end + 1;
    }
    return sentence;
}

void print_mnemonics_helper(std::uint32_t length, std::uint32_t digits,
                            std::string mnemonic) {
    const static constexpr char chars[][10] = {{},
                                         {'a', 'b', 'c'},
                                         {'d', 'e', 'f'},
                                         {'g', 'h', 'i'},
                                         {'j', 'k', 'l'},
                                         {'m', 'n', 'o'},
                                         {'p', 'q', 'r', 's'},
                                         {'t', 'u', 'v'},
                                         {'w', 'x', 'y', 'z'}};

    if (length == 0) {
        std::cout << mnemonic << std::endl;
        return;
    }

    auto const digit = digits / length;
    if (digit == 0) {
        print_mnemonics_helper(length / 10, digits % length, mnemonic);
    } else {
        auto const char_count = ((digit == 7) || (digit == 9)) ? 4 : 3;
        for (auto i = 0; i < char_count; ++i) {
            print_mnemonics_helper(length / 10, digits % length,
                                   mnemonic + chars[digit][i]);
        }
    }
}

// recursive backtracking algorithm to pringt all words that could be expressed
// (even unreasonable ones) using the keypad on a phone
void print_mnemonics(std::uint32_t digits) {
    if (digits == 0) return;

    auto const length = pow(10,floor(log10(digits)));
    print_mnemonics_helper(length, digits, "");
}

// runlength encoding/decoding for non-digit strings (no error checking, requires valid input)
namespace runlength
{
    std::string encode(std::string const& str)
    {
        std::ostringstream oss;
        auto itr = str.begin();
        while( itr != str.end() )
        {
            auto end = std::find_if_not(itr,str.end(),[itr](char const c){ return c == *itr; });
            oss << std::distance(itr,end) << *itr;
            itr = end;
        }
        return oss.str();
    }

    std::string decode(std::string const& str)
    {
        std::istringstream iss(str);
        std::ostringstream oss;
        std::uint32_t count;
        while( iss >> count )
        {
            char c;
            iss >> c;
            while(count--)
                oss << c;
        }
        return oss.str();
    }
} // namespace runlength

}  // namespace strings
}  // namespace eopi

#endif  // EOPI_STRINGS_HPP_
