#ifndef EOPI_STRINGS_HPP_
#define EOPI_STRINGS_HPP_

#include <algorithm>
#include <bitset>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>

namespace eopi {
namespace strings {

inline void remove_and_replace(std::size_t input_size, std::string& result) {
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
inline bool is_palindrom(std::string const& str) {
    auto itr = str.begin();
    auto ritr = str.rbegin();
    for (std::size_t i = 0; 2 * i < str.size(); ++i, ++itr, ++ritr)
        if (*itr != *ritr) return false;
    return true;
}

inline std::string reverse_words(std::string sentence) {
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

inline void print_mnemonics_helper(std::uint32_t length, std::uint32_t digits,
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
inline void print_mnemonics(std::uint32_t digits) {
    if (digits == 0) return;

    auto const length = pow(10, floor(log10(digits)));
    print_mnemonics_helper(length, digits, "");
}

// runlength encoding/decoding for non-digit strings (no error checking,
// requires valid input)
namespace runlength {
inline std::string encode(std::string const& str) {
    std::ostringstream oss;
    auto itr = str.begin();
    while (itr != str.end()) {
        auto end = std::find_if_not(itr, str.end(),
                                    [itr](char const c) { return c == *itr; });
        oss << std::distance(itr, end) << *itr;
        itr = end;
    }
    return oss.str();
}

inline std::string decode(std::string const& str) {
    std::istringstream iss(str);
    std::ostringstream oss;
    std::uint32_t count;
    while (iss >> count) {
        char c;
        iss >> c;
        while (count--) oss << c;
    }
    return oss.str();
}
}  // namespace runlength

namespace elias_gamma_code {
inline std::string encode(std::vector<std::uint32_t> const& data) {
    auto const to_binary = [](auto const val) {
        std::ostringstream oss;
        oss << std::bitset<32>(val);
        auto const str = oss.str();
        return str.substr(str.find_first_of("1"));
    };

    std::ostringstream result;
    for (auto val : data) {
        auto const str = to_binary(val);
        auto len = str.size();
        while (--len) result << "0";
        result << str;
    }
    return result.str();
}

inline std::vector<std::uint32_t> decode(std::string const& encoded) {
    std::vector<std::uint32_t> result;

    std::size_t pos = 0;
    while (pos < encoded.size()) {
        auto start = encoded.find_first_of("1", pos);
        auto len = start - pos + 1;
        auto num = encoded.substr(start, len);
        result.push_back(std::stoi(num, nullptr, 2));
        pos = start + len;
    }

    return result;
}
}  // namespace elias_gamma_code

// print justified text
inline void print_justified(std::vector<std::string> const& text,
                            std::uint32_t const justification) {
    for (std::size_t pos = 0, end = 0; pos < text.size(); pos = end) {
        std::uint32_t count = text[pos].size();
        ++end;
        while (end < text.size() &&
               count + text[end].size() + 1 <= justification) {
            count += text[end].size() + 1;
            ++end;
        }

        // last line, print unjustified
        if (end == text.size()) {
            std::cout << text[pos];
            for (auto i = pos + 1; i < end; ++i) {
                std::cout << " " << text[i];
            }
            std::cout << std::endl;
        } else  // print justified
        {
            auto const n = end - pos;
            auto const spaces = justification - count + n - 1;
            auto const sep = spaces / (n - 1);

            std::cout << text[pos];
            for (auto i = 1; i < n; ++i) {
                // add spaces + additional one if we got a remainder
                for (auto k = 0;
                     k < sep + ((i - 1 < (spaces % (n - 1))) ? 1 : 0); ++k)
                    std::cout << " ";

                std::cout << text[pos + i];
            }
            std::cout << std::endl;
        }
    }
}

// rabin karp string search, expecting only basic chars, can offer worse
// complexity for mixed patterns
inline std::size_t rabin_karp(const std::string& text,
                              const std::string& pattern) {
    // on large patterns, we cannot find the pattern in the text
    if (pattern.size() > text.size()) return std::string::npos;

    const constexpr std::uint32_t modul = 30402457;
    const constexpr std::uint32_t base =
        26;  // number of chars, ignoring capitalisation

    std::uint32_t max_power = 1;
    for (std::size_t i = 1; i < pattern.size(); ++i)
        max_power = (max_power * base) % modul;

    // interpret a string as number (base 26). We compute the value of the
    // string modul a prime
    auto const get_hash = [base, modul](auto begin, auto const end) {
        std::int64_t hash = 0;
        for (auto itr = begin; itr != end; ++itr)
            hash = (hash * base + *itr) % modul;
        return hash;
    };

    // compute current hashes
    auto const pattern_hash = get_hash(pattern.begin(), pattern.end());
    auto local_text_hash =
        get_hash(text.begin(), text.begin() + pattern.size());

    // check for collisions
    auto const match = [&](const auto pos) {
        return 0 == text.compare(pos - pattern.size(), pattern.size(), pattern);
    };

    auto pos = text.begin() + pattern.size();
    for (std::size_t pos = pattern.size(); pos < text.size(); ++pos) {
        if (pattern_hash == local_text_hash && match(pos))
            return pos - pattern.size();

        // advance the search, by moving the hash function. Updating the hash to
        // reflect the next position. This removes power * t[0] (the largest
        // number) and adds the new char
        local_text_hash -= ((text[pos - pattern.size()] * max_power) % modul);
        if (local_text_hash < 0) local_text_hash += modul;
        local_text_hash = (local_text_hash * base + text[pos]) % modul;
    }

    // if there is a match at the final position
    if ((pattern_hash == local_text_hash) && match(text.size()))
        return text.size() - pattern.size();

    return std::string::npos;
};

}  // namespace strings
}  // namespace eopi

#endif  // EOPI_STRINGS_HPP_
