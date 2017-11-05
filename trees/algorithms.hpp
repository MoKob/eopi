#ifndef EOPI_TREES_ALGORITHMS_HPP_
#define EOPI_TREES_ALGORITHMS_HPP_

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

#include <iostream>

namespace eopi {
namespace trees {
namespace algorithms {
std::vector<std::pair<int, char>>
view_from_above(std::vector<std::tuple<int, int, int, char>> const &ranges) {
  // organise the tuples into begin/end events
  std::vector<std::tuple<int, bool, std::size_t>> events;
  events.reserve(2 * ranges.size());
  for (std::size_t i = 0; i < ranges.size(); ++i) {
    auto const &r = ranges[i];
    events.push_back({std::get<1>(r), false, i});
    events.push_back({std::get<2>(r), true, i});
  }

  std::sort(events.begin(), events.end(), [&](auto const &lhs,
                                              auto const &rhs) {
    // group by pos, start
    if (std::tie(std::get<0>(lhs), std::get<1>(lhs)) <
        std::tie(std::get<0>(rhs), std::get<1>(rhs)))
      return true;
    if (std::tie(std::get<0>(lhs), std::get<1>(lhs)) >
        std::tie(std::get<0>(rhs), std::get<1>(rhs)))
      return false;
    // group same pos/start/end by height and break ties with the ID
    return std::tie(std::get<0>(ranges[std::get<2>(lhs)]), std::get<2>(lhs)) >
           std::tie(std::get<1>(ranges[std::get<2>(rhs)]), std::get<2>(rhs));
  });

  std::vector<std::pair<int, char>> results;
  std::set<std::pair<int, int>> active_ranges;

  for (std::size_t i = 0; i < events.size();) {
    int pos;
    do {
      int id;
      bool end;
      std::tie(pos, end, id) = events[i];
      if (end) {
        // end-event
        active_ranges.erase({std::get<0>(ranges[id]), id});
      } else {
        // new-range
        active_ranges.insert({std::get<0>(ranges[id]), id});
      }
      ++i;
    } while (i < events.size() &&
             std::get<0>(events[i - 1]) == std::get<0>(events[i]));

    if (active_ranges.empty()) {
      results.push_back({pos, 0});
    } else {
      auto above = *active_ranges.rbegin();
      auto above_id = above.second;
      if (results.empty() ||
          results.back().second != std::get<3>(ranges[above_id]))
        results.push_back({pos, std::get<3>(ranges[above_id])});
    }
  }

  return results;
}
} // namespace algorithm
} // namespace trees
} // namespace eopi

#endif // EOPI_TREES_ALGORITHMS_HPP_
