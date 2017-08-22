#ifndef EOPI_STRINGS_RANDOM_HPP_
#define EOPI_STRINGS_RANDOM_HPP_

#include <algorithm>
#include <cstdint>
#include <string>

namespace eopi {
namespace strings {

// compute the look and say sequence for a given repetition
inline std::string look_and_say(std::uint32_t n) {
    std::string current = "1";
    while (--n) {
        std::string tmp = current;
        current = "";
        auto it = tmp.begin();
        while (it != tmp.end()) {
            auto end = std::find_if(it, tmp.end(),
                                    [it](auto const c) { return c != *it; });
            current += std::to_string(std::distance(it, end));
            current += *it;
            it = end;
        }
    }
    return current;
}

// roman numeral to int
inline std::uint32_t from_roman(std::string const numerals) {
    // M -> 1000
    // D -> 500
    // C -> 100
    // L -> 50
    // X -> 10
    // V -> 5
    // I -> 1
    auto const to_number = [](auto const c) {
        switch (c) {
            case 'M':
                return 1000;
            case 'D':
                return 500;
            case 'C':
                return 100;
            case 'L':
                return 50;
            case 'X':
                return 10;
            case 'V':
                return 5;
            case 'I':
                return 1;
            default:
                return 0;
        }
    };

    auto last = 0;
    std::uint32_t total = 0;
    for (auto itr = numerals.rbegin(); itr != numerals.rend(); ++itr) {
        auto cur = to_number(*itr);
        if (cur < last)
            total -= cur;
        else
            total += cur;
        last = cur;
    }
    return total;
}

inline void ip_helper(std::uint32_t to_place, std::uint32_t pos,
                      std::string const &str, int placements[3]) {
    // can use at least three digits per dot
    if ((str.length() - pos) > 3 * (to_place + 1)) return;

    // output the placements
    if (to_place == 0) {
        if (std::stoi(str.substr(pos)) < 256) {
            std::cout << str.substr(0, placements[0]) << '.';
            std::cout << str.substr(placements[0],
                                       placements[1] - placements[0])
                      << '.';
            std::cout << str.substr(placements[1],
                                       placements[2] - placements[1])
                      << '.';
            std::cout << str.substr(placements[2],
                                       str.size() - placements[2])
                      << std::endl;
        }
        return;
    }

    // backtrack
    for( int i = 1; i < 4 && pos + i < str.length(); ++i)
    {
        placements[3-to_place] = pos + i;
        if( std::stoi(str.substr(pos,i)) < 256)
            ip_helper(to_place - 1, i+pos, str, placements);
    }
}

inline void all_valid_ips(std::string const ip) {
    int placements[3];
    ip_helper(3,0,ip,placements);
}

}  // namespace strings
}  // namespace eopi

#endif  // EOPI_STRINGS_RANDOM_HPP_
