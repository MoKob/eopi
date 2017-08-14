#ifndef EOPI_ARRAYS_ALGORITHMS_HPP_
#define EOPI_ARRAYS_ALGORITHMS_HPP_

#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>

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

// using dynamic programming to compute the best we can reach with num_buys
// buy-sells in values
std::uint64_t max_difference(std::vector<std::int32_t> const& values,
                             std::int32_t const num_buys) {
    if (2 * num_buys >= values.size()) return max_difference_infinite(values);

    // whats the best we can do when having to do j-1 buy / sell actions with j
    // happening at i
    // whats the best we can do when doing j-1 buy/sell transactions and selling
    // at i
    const auto state_size = 2 * num_buys + 1;
    std::vector<std::int64_t> buys_and_sells(
        state_size, std::numeric_limits<std::int32_t>::min());
    buys_and_sells[0] = 0;

    std::cout << std::endl;
    for (std::uint32_t i = 0; i < values.size(); ++i) {
        auto last_round = buys_and_sells;
        for (std::int32_t k = 1, sign = -1; k <= i + 1 && k < state_size;
             ++k, sign *= -1) {
            std::int64_t diff = sign * values[i] + last_round[k - 1];
            buys_and_sells[k] = std::max(buys_and_sells[k], diff);
        }
    }
    return buys_and_sells.back();
}

// compute the product (without considering overflows) of all entries in values,
// excluding one entry
std::int64_t max_product_all_but_one(std::vector<std::int32_t> const& values) {
    // count negative values
    auto negatives = std::count_if(values.begin(), values.end(),
                                   [](auto val) { return val < 0; });

    std::int64_t product = 1;

    // uneven number of negatives
    if (negatives % 2 == 1) {
        // we can use all negatives but the smalles one (both for all
        // negative/not all), after run state will hold the smallest (absolute)
        // negative value
        return std::accumulate(
            values.begin(), values.end(), product,
            [state = 1](auto product, auto value) mutable {
                if (value < 0 && (state == 1 || state < value)) {
                    auto new_product = state * product;
                    state = value;
                    return new_product;
                } else
                    return product * value;

            });
    } else {
        // we will have a negative result, leave out the largest
        if (negatives == values.size()) {
            // when done, state will hold the largest (abs) negative values
            return std::accumulate(
                values.begin(), values.end(), product,
                [state = 1](auto product, auto value) mutable {
                    if (value < 0 && (value < state)) {
                        auto new_product = state * product;
                        state = value;
                        return new_product;
                    } else
                        return product * value;
                });

        } else {
            // use all negatives, leave out smallest positives, after running
            // state will hold the smallest positive value
            return std::accumulate(
                values.begin(), values.end(), product,
                [state = -1](auto product, auto value) mutable {
                    if (value >= 0 && (state == -1 || value < state)) {
                        auto new_product = std::abs(state) * product;
                        state = value;
                        return new_product;
                    } else
                        return product * value;
                });
        }
    }

    return 0;
}

std::pair<std::uint32_t, std::uint32_t> max_increasing_subarray(
    std::vector<std::int32_t> const& values) {
    auto best = std::make_pair(0u, 0u);

    std::uint32_t start, current;

    auto const update = [&]() {
        auto new_pair = std::make_pair(start, current);
        start = current;
        if (best.second - best.first < new_pair.second - new_pair.first)
            best = new_pair;
    };

    for (start = 0, current = 1; current < values.size(); ++current) {
        // end of a sequence
        if (values[current] < values[current - 1]) update();
    }

    update();

    return best;
}

// permute up to 2^31 entries, implicitly borrowing a sign bit
std::vector<std::int32_t> apply_permutation(
    std::vector<std::int32_t> input_output,
    std::vector<std::int32_t> & permutation) {

    // permute one entire circle
    auto const permute_circle = [&](auto const start)
    {
        auto pos = permutation[start];
        auto tmp = input_output[start];
        while( pos != start )
        {
            std::swap(tmp,input_output[pos]);
            auto tmp_pos = pos;
            pos = permutation[pos];
            permutation[tmp_pos] = -permutation[tmp_pos];
        }
        input_output[start] = tmp;
    };

    for( std::uint32_t start = 0; start < input_output.size(); ++start )
    {
        if( permutation[start] > 0)
            permute_circle(start);
        else
            permutation[start] = -permutation[start];
    }

    return input_output;
}

}  // namespace arrays
}  // namespace eopi

#endif  // EOPI_ARRAYS_ALGORITHMS_HPP_
