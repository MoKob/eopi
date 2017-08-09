#ifndef EOPI_ARRAYS_ALGORITHMS_HPP_
#define EOPI_ARRAYS_ALGORITHMS_HPP_

#include <algorithm>
#include <functional>
#include <iterator>

namespace eopi {
namespace arrays {

// three wya partition
// input: an array of values, comparable for less
// output and array with the elements less | equal | greater to the pivot
// element
// less needs to allow comp(pivot,*itr) and comp(*itr,pivot)
template <typename iterator_type, typename pivot_type, typename comparator_type>
void three_way_partition(const iterator_type begin, const iterator_type end,
                         const pivot_type pivot, comparator_type less) {
    static_assert(
        std::is_convertible<std::random_access_iterator_tag,
                            typename std::iterator_traits<
                                iterator_type>::iterator_category>::value,
        "The iterators for three_way_partition need to be convertable to "
        "random access iterators.");

    auto smaller = begin, equal = begin, larger = end;
    while (equal != larger) {
        if (less(*equal, pivot)) {
            // element at equal is less than pivot
            std::swap(*smaller, *equal);
            ++smaller, ++equal;
        } else if (less(pivot, *equal)) {
            // element at *equal is larger and can be stored at the end
            --larger;
            std::swap(*equal, *larger);
        } else {
            // element is equal
            ++equal;
        }
    }
}

template <typename iterator_type, typename pivot_type>
void three_way_partition(const iterator_type begin, const iterator_type end,
                         const pivot_type pivot) {
    three_way_partition(begin, end, pivot, std::less<pivot_type>());
}

template <typename iterator_type, typename key_type>
iterator_type remove(iterator_type const begin, iterator_type const end,
                     key_type const key) {
    auto new_end = begin;  // all elements before new_end are != key
    auto itr = begin;
    while (itr != end) {
        if (*itr != key) *new_end++ = *itr;
        ++itr;
    }

    return new_end;
}

template <typename iterator_type>
iterator_type unique(iterator_type const begin, iterator_type const end) {
    if (begin == end) return end;

    auto new_end = begin + 1;  // all elements prior to new_end are unique
    auto itr = new_end;
    while (itr != end) {
        // new element found
        if (*(new_end - 1) != *itr) {
            *new_end = *itr;
            ++new_end;
        }
        ++itr;
    }
    return new_end;
}

// find the smallest positive integer missing in data. Destroys the content of
// data
std::int32_t smallest_missing_positive(std::vector<std::int32_t>& data) {
    for (std::size_t i = 0; i < data.size();) {
        if (data[i] != i && data[i] < data.size() && data[i] >= 0) {
            std::swap(data[i], data[data[i]]);
        } else {
            ++i;
        }
    }
    for (std::size_t i = 0; i < data.size(); ++i) {
        // all elements should now contain their identity
        if (data[i] != i) return i;
    }
    // all integers present
    return -1;
}

std::uint32_t max_difference(std::vector<std::int32_t> const& values) {
    // find the minimum b such that a little robot with capacity `b` in batter,
    // perfect recuperation and potential energy == capacity can traverse the
    // entire sequence
    // The basic observations are: at the start and at every new low-point, the
    // battery will be fully charged. We need to find the maximum difference
    // between h_i and h_j with i < j.
    if (values.empty()) return 0;

    auto current_min = values.front();
    std::uint32_t diff = 0;
    for (auto val : values) {
        if (val < current_min)
            current_min = val;
        else
            diff =
                std::max(diff, static_cast<std::uint32_t>(val - current_min));
    }
    return diff;
}

// find i < j < k < l such that values[j]-values[i] + values[k] - values[l]
// maximal over all i,j,k,l
std::uint64_t max_difference_twice(std::vector<std::int32_t> const& values) {
    if (values.empty()) return 0;

    // use additional storage to memorize max difference values for all v[j]
    std::vector<std::uint32_t> best_forward(values.size());

    auto current_min = values.front();
    std::uint32_t diff = 0;

    auto const best_diff_until = [&](auto const val) {
        if (val < current_min) current_min = val;

        return diff = std::max(diff,
                               static_cast<std::uint32_t>(val - current_min));
    };
    // store the best differences into best_forward
    std::transform(values.begin(), values.end(), best_forward.begin(),
                   best_diff_until);

    // now to a backwards pass and compute the maximum from the first_half and
    // the second half in combination
    std::uint32_t total_best = 0;
    diff = 0;
    auto current_max = values.back();
    for (std::size_t i = 0; i < values.size(); ++i) {
        auto val = values[values.size() - i - 1];
        if (val > current_max)
            current_max = val;
        else {
            diff =
                std::max(diff, static_cast<std::uint32_t>(current_max - val));
            total_best = std::max(
                total_best, diff + best_forward[best_forward.size() - i - 1]);
        }
    }

    return total_best;
}

// maximum gain when buying and selling as often as we want
std::uint64_t max_difference_infinite(std::vector<std::int32_t> const& values) {
    // when selling and buying without a limit, we can take all profits there
    // are
    std::uint64_t sum = 0;
    auto sum_positives = [&sum](auto const lhs, auto const rhs) {
        if (lhs < rhs) sum += rhs - lhs;
        return false;
    };
    std::adjacent_find(values.begin(), values.end(), sum_positives);
    return sum;
}

}  // namespace arrays
}  // namespace eopi

#endif  // EOPI_ARRAYS_ALGORITHMS_HPP_
