#ifndef EOPI_SEARCH_ALGORITHMS_HPP_
#define EOPI_SEARCH_ALGORITHMS_HPP_

namespace eopi {
namespace search {
namespace algorithm {

// find the first occurence between begin/end (exclusive) of
template <typename RandomAccessIT, typename T>
RandomAccessIT lower_bound(RandomAccessIT begin, RandomAccessIT end,
                           T const &value) {
  while (begin != end) {
    auto middle = begin + (end - begin) / 2;
    // element in the range [middle+1,end)
    if (*middle < value) {
      begin = middle + 1;
    } else {
      // element in the range [begin,end]
      end = middle;
    }
  }
  return begin;
}

} // namespace algorithm
} // namespace search
} // namespace eopi

#endif // EOPI_SEARCH_ALGORITHMS_HPP_
