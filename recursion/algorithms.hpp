#ifndef EOPI_RECURSION_ALGORITHMS_HPP_
#define EOPI_RECURSION_ALGORITHMS_HPP_

#include <cstdint>
#include <iostream>

namespace eopi {
namespace recursion {
namespace algorithms {

namespace details {

void hanoi_helper(std::int32_t from, std::int32_t to, std::uint32_t discs) {
  if (discs == 0)
    return;
  hanoi_helper(from, 3 - from - to, discs - 1);
  std::cout << "Move disc " << discs << " from " << from << " to " << to
            << std::endl;
  hanoi_helper(3 - from - to, to, discs - 1);
}

// check a known position for a match
bool match_strict(std::string const &str, std::size_t pos_str,
                  std::string const &regex, std::size_t pos_regex) {
  // advance the reg-ex from the current position
  for (; pos_str < str.size() && pos_regex < regex.size();
       ++pos_str, ++pos_regex) {
    // not at end of line, but need to be?
    if (regex[pos_regex] == '$')
      return false;

    // can match, but do not need to match
    if (pos_regex + 1 < regex.size() && regex[pos_regex + 1] == '*') {
      // zero length matching of char
      std::size_t new_pos_str = pos_str;
      do {
        // match at str position, starting with all chars after a match for *
        if (match_strict(str, new_pos_str, regex, pos_regex + 2))
          return true;
        ++new_pos_str;
      } while (new_pos_str < str.size() &&
               (regex[pos_regex] == '.' ||
                (str[new_pos_str - 1] == regex[pos_regex])));
    } else {
      // can we match the curren char?
      if (str[pos_str] != regex[pos_regex] && regex[pos_regex] != '.')
        return false;
    }
  }

  // end of line match
  if (pos_regex < regex.size()) {
    if (regex[pos_regex] == '$')
      return true;
    if ((regex.size() - pos_regex) % 2 == 1 && regex.back() != '$')
      return false;
    for (; pos_regex + 2 < regex.size(); pos_regex += 2) {
      if (regex[pos_regex] != '*')
        return false;
    }
    return true;
  }

  // matched all?
  return true;
}

} // namespace details

// print a sequence of moves to solve the towers of hanoi for n towers
inline void hanoi(std::uint32_t n) { details::hanoi_helper(0, 1, n); }

inline bool esre_match(std::string str, std::string esre) {
  // if we start with X* or need to match in front
  if ((esre.size() > 2 && esre[1] == '*') || esre.front() == '$')
    return details::match_strict(str, 0, esre, (esre.front() == '$' ? 1 : 0));

  for (std::size_t pos = 0; pos < str.size(); ++pos) {
    // check all possible starting positions
    if ((str[pos] == esre[0] || esre[0] == '.') &&
        details::match_strict(str, pos, esre, 0))
      return true;
  }

  return false;
}

} // namespace algorithms
} // namespace recursion
} // namespace eopi

#endif // EOPI_RECURSION_ALGORITHMS_HPP_
