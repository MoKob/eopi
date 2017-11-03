#ifndef EOPI_HASH_ALGORITHMS_HPP_
#define EOPI_HASH_ALGORITHMS_HPP_

#include <algorithm>
#include <iostream>
#include <limits>
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

inline bool has_palindromic_permutation(std::string const &str) {
  int odd = 0;
  std::unordered_map<char, bool> odd_count;
  for (auto c : str) {
    odd_count[c] = !odd_count[c];
    if (odd_count[c])
      ++odd;
    else
      --odd;
  }
  // at most a single odd element
  return odd <= 1;
}

// find the mimimum distance between two repeated words
inline std::uint32_t
closest_repeated_pair(std::vector<std::string> const &words) {
  std::unordered_map<std::string, std::uint32_t> last_pos;
  std::unordered_map<std::string, std::uint32_t> min_dist;

  for (std::size_t i = 0; i < words.size(); ++i) {
    auto const &word = words[i];
    auto itr = last_pos.find(word);
    if (itr == last_pos.end()) {
      min_dist[word] = std::numeric_limits<std::uint32_t>::max();
    } else {
      min_dist[word] =
          std::min<std::uint32_t>(min_dist[word], i - last_pos[word]);
    }
    last_pos[word] = i;
  }

  std::uint32_t min = min_dist.begin()->second;
  for (auto const &p : min_dist) {
    if (p.second < min)
      min = p.second;
  }
  return min;
}

// find the smallest sub-array that covers all keywords
inline std::pair<std::uint32_t, std::uint32_t>
digest(std::vector<std::string> const &text,
       std::vector<std::string> const &keywords) {
  // prepare a map of the keywords
  std::unordered_map<std::string, std::uint32_t> count;
  for (auto const &key : keywords)
    count[key] = 0;

  std::uint32_t covered = 0, best_begin = 0, best_end = text.size();
  for (std::size_t begin = 0, end = 0; end < text.size(); ++end) {
    auto itr = count.find(text[end]);
    if (itr != count.end()) {
      // newly covering an elment
      if (itr->second == 0) {
        ++covered;
        itr->second += 1;
      }

      // now covering all elements
      if (covered == keywords.size()) {
        // shift begin forward, so that we still cover all elements
        while (covered == keywords.size()) {
          auto begin_itr = count.find(text[begin]);
          if (begin_itr != count.end()) {
            begin_itr->second -= 1;
            if (begin_itr->second == 0)
              --covered;
          }
          ++begin;
        }
        if (end - begin + 2 < best_end - best_begin) {
          best_begin = begin - 1;
          best_end = end + 1;
        }
      }
    }
  }
  return {best_begin, best_end};
}

} // namespace algorithms
} // namespace hash
} // namespace eopi

#endif // EOPI_HASH_ALGORITHMS_HPP_
