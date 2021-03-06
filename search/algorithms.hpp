#ifndef EOPI_SEARCH_ALGORITHMS_HPP_
#define EOPI_SEARCH_ALGORITHMS_HPP_

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <utility>
#include <vector>

namespace eopi {
namespace search {

namespace tool {
// for an increasing function returning an int and a valid range, this mimics an
// unbound array. Throws an exception on out-of-bounds acces
template <typename functor> class UnboundArray {
public:
  UnboundArray(std::size_t size, functor func) : size(size), func(func) {}

  std::uint64_t operator[](std::size_t index) const {
    if (index >= size)
      throw std::out_of_range("Index is out of array bounds");

    else
      return func(index);
  }

private:
  std::size_t size;
  functor func;
};

template <typename T> UnboundArray<T> make_array(std::size_t size, T func) {
  return UnboundArray<T>(size, func);
}

} // namespace tool

namespace algorithm {

// find the first occurence between begin/end (exclusive) of
template <typename RandomAccessIT, typename T>
RandomAccessIT lower_bound(RandomAccessIT begin, RandomAccessIT end,
                           T const &value) {
  auto not_found = end;
  while (begin != end) {
    auto middle = begin + (end - begin) / 2;
    if (*middle < value) {
      // element in the range [middle+1,end)
      begin = middle + 1;
    } else {
      // element in the range [begin,middle]
      end = middle;
    }
  }
  return (*begin < value) ? begin : not_found;
}

template <typename RandomAccessIT, typename T>
RandomAccessIT upper_bound(RandomAccessIT begin, RandomAccessIT end,
                           T const &value) {
  while (begin != end) {
    auto middle = begin + (end - begin) / 2;
    if (value < *middle) {
      // first larger is in range [begin,middle]
      end = middle;
    } else {
      // element in range [middle+1,end)
      begin = middle + 1;
    }
  }
  return begin;
}

// find any key for which it's index matches it's value in a sorted array of
// distinct values
inline std::size_t
find_index_value_match(std::vector<std::int32_t> const &values) {
  // the entire array is potentially invalid
  if (!values.empty() &&
      (values.front() > 0 ||
       values.back() < static_cast<std::int32_t>(values.size())))
    return -1;

  std::size_t begin = 0, end = values.size();
  while (begin < end) {
    int middle = begin + (end - begin) / 2;
    if (values[middle] == middle)
      return middle;

    if (values[middle] < middle) {
      // invalidates the left side, due to the pidgeonhole principle and
      // decreasing numbers
      begin = middle + 1;
    } else {
      // values[middle] > middle -> all values [middle,end) are larger than
      // their index
      end = middle;
    }
  }

  // if no item is found
  return (static_cast<std::int32_t>(begin) == values[begin]) ? begin : -1;
}

template <typename array_type, typename value_type>
std::size_t find_unbound(array_type const &array, value_type const &key) {
  std::size_t begin = 0, count = 1,
              end = std::numeric_limits<std::size_t>::max();

  // find a good end for the array
  while (begin < end) {
    try {
      auto val = array[count];
      if (val == key)
        return count;
      else if (val > key) {
        end = count - 1;
        auto middle = begin + (end - begin) / 2;
        count = middle;
      } else {
        // val < key
        begin = count + 1;
        auto middle = begin + (end - begin) / 2;
        count = std::min(2 * count, middle + 1);
      }
    } catch (std::out_of_range except) {
      // out of range -> array has at most begin+count elements
      end = count;
      count = begin + (end - begin) / 2;
    }
  }
  // check if found
  return -1;
}

// find the k-th largest element of the array represented by the merge of lhs
// and rhs
inline std::int32_t kth_element_dual(std::uint32_t k,
                                     std::vector<std::int32_t> const &lhs,
                                     std::vector<std::int32_t> const &rhs) {

  if (lhs.size() + rhs.size() < k)
    throw std::out_of_range("Supplied arrays do not offer K elements");

  // define a range [a,b] and x in [a,b] so that we use k-x elements from
  // lhs and x elements from rhs
  std::size_t begin = k < rhs.size() ? 0 : k - rhs.size(),
              end = std::min<std::uint32_t>(lhs.size(), k);
  // binary search for x on the range
  while (begin < end) {
    auto middle = begin + (end - begin) / 2;
    auto candidate = std::min(lhs[middle], rhs[k - middle]);
    if (k - middle + 1 < rhs.size() && rhs[k - middle + 1] < candidate) {
      // we need to select at least k-middle+1 elements from rhs
      end = middle;
    } else if (middle + 1 < lhs.size() && lhs[middle + 1] < candidate) {
      // we need more or equal to middle+1 elements from the lhs
      begin = middle + 1;
    } else {
      return candidate;
    }
  }

  return std::min(lhs.front(), rhs.front());
}

// find a value in a 2d array
inline bool find_2d(std::vector<std::vector<int>> const &field, int value) {
  std::int32_t col = field[0].size() - 1, row = 0;
  while (static_cast<std::size_t>(row) < field.size() && col >= 0) {
    if (field[row][col] == value)
      return true;
    if (field[row][col] < value) {
      ++row;
    } else {
      --col;
    }
  }
  return false;
}

// find the min/max with less than 2n-1 comparisons
template <typename value_type>
std::pair<std::size_t, std::size_t>
min_max(std::vector<value_type> const &data) {
  std::size_t min = 0, max = 0;
  for (std::size_t i = 0; i + 1 < data.size(); i += 2) {
    std::size_t less = i, more = i + 1;
    if (data[i + 1] < data[i]) {
      less = i + 1;
      more = i;
    }

    if (data[less] < data[min])
      min = less;
    if (data[max] < data[more])
      max = more;
  }
  if (data.size() % 2 == 1) {
    if (data.back() < data[min])
      min = data.size() - 1;
    if (data[max] < data.back())
      max = data.size() - 1;
  }
  return {min, max};
}

template <typename randitr, typename value_type>
randitr partition(randitr begin, randitr end, value_type const pivot) {
  randitr less = begin, equal = begin, larger = end;
  while (equal != larger) {
    if (*equal < pivot) {
      std::swap(*less, *equal);
      ++less;
      ++equal;
    } else if (*equal > pivot) {
      --larger;
      std::swap(*equal, *larger);
    } else {
      // equal
      ++equal;
    }
  }
  // end of the less range is the beginning of the qual range
  return less;
}

template <typename value_type>
value_type quick_select(std::size_t const k, std::vector<value_type> &data) {
  std::size_t begin = 0, end = data.size();
  while (begin < end) {
    auto pivot = data[begin + (end - begin) / 2];

    // partition into <= pivot, > pivot
    auto const pivot_itr = eopi::search::algorithm::partition(
        data.begin() + begin, data.begin() + end, pivot);
    auto const pivot_index =
        static_cast<std::size_t>(std::distance(data.begin(), pivot_itr));
    if (pivot_index == k)
      return pivot;
    if (pivot_index < k)
      begin = pivot_index + 1;
    else
      end = pivot_index;
  }
  throw std::out_of_range("Less than k elements provided");
}

// in a vector of distinc elements, except for a single one that has replaced a
// missing number, find what is the missing and what is the duplicate
std::pair<std::uint32_t, std::uint32_t>
missing_and_duplicate(std::vector<std::uint32_t> const &values) {
  std::uint64_t full_sum = values.size() * (values.size() + 1) / 2;
  auto const part_sum =
      std::accumulate(values.begin(), values.end(), std::uint64_t{0});
  std::uint32_t full_xor = 0;
  std::uint32_t part_xor = 0;
  for (std::size_t i = 0; i < values.size(); ++i) {
    full_xor ^= (i + 1);
    part_xor ^= values[i];
  }

  auto miss_xor_dup = full_xor ^ part_xor;
  for (std::uint32_t dup = 1; dup <= values.size(); ++dup) {
    auto miss = miss_xor_dup ^ dup;
    if (part_sum - dup + miss == full_sum)
      return {miss, dup};
  }
  return {0, 0};
}

// in an array where each element is present exactly three times, except for one
// which is present 1 times, fine the element present only once
std::uint32_t once(std::vector<std::uint32_t> const &data) {
  std::uint32_t lsb = 0, msb = 0;
  for (auto v : data) {
    // bitwise sum of v and the bit-sum stored in the combination of msb | lsb
    // modulo three
    auto carry = lsb & v;
    // if carry == 1 for bit j, then msb[j] == 0
    msb |= carry;
    lsb ^= v;

    // compute modulo three
    auto both = lsb & msb;
    msb ^= both;
    lsb ^= both;
  }
  return lsb;
}

} // namespace algorithm
} // namespace search
} // namespace eopi

#endif // EOPI_SEARCH_ALGORITHMS_HPP_
