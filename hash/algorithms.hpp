#ifndef EOPI_HASH_ALGORITHMS_HPP_
#define EOPI_HASH_ALGORITHMS_HPP_

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace eopi {
namespace hash {
namespace algorithms {

// output the list of all anagrams of a string
inline void list_anagrams(std::vector<std::string> const &wordlist) {
  std::unordered_map<std::string, std::vector<std::string>> anagrams;
  for (auto const &s : wordlist) {
    auto copy = s;
    std::sort(copy.begin(), copy.end());
    anagrams[copy].emplace_back(s);
  }

  for (auto const &group : anagrams) {
    std::cout << "Group:";
    for (auto const &element : group.second)
      std::cout << " " << element;
    std::cout << std::endl;
  }
}

} // namespace algorithms
} // namespace hash
} // namespace eopi

#endif // EOPI_HASH_ALGORITHMS_HPP_
