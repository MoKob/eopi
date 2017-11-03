#ifndef EOPI_SEARCH_ALGORITHMS_HPP_
#define EOPI_SEARCH_ALGORITHMS_HPP_

#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
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

} // namespace algorithm
} // namespace search
} // namespace eopi

#endif // EOPI_SEARCH_ALGORITHMS_HPP_
