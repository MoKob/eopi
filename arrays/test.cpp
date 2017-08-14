#include <iomanip>
#include <iostream>

#include <vector>

#include "algorithms.hpp"
#include "bigint.hpp"
#include "randoms.hpp"
#include "primes.hpp"

using namespace std;

template <typename int_type>
void print(vector<int_type> const& vec) {
    cout << "[vector]";
    for (auto e : vec) cout << " " << e;
    cout << endl;
}

int main() {
    vector<int> data = {1, 2, 4, 1, 1, 3, 4, 3, 3, 4, 2, 3, 1};

    cout << "Partitioning by pivot 3:\n";
    print(data);
    eopi::arrays::three_way_partition(data.begin(), data.end(), 3);
    print(data);

    eopi::arrays::BigInt value("1234567891234567891234567890");
    cout << "Big value: " << value << endl;
    ++value;
    cout << "Big value incremented: " << value << endl;
    eopi::arrays::BigInt nine("999999999");
    cout << nine << "++ = " << ++nine << endl;
    eopi::arrays::BigInt minus("-1000000000");
    cout << minus << "++ = " << ++minus << endl;

    // boardgames:
    vector<std::uint32_t> winable = {1, 3, 0, 0, 4, 0, 0, 0};
    vector<std::uint32_t> not_winable = {1, 3, 0, 0, 0, 4, 0, 1};
    cout << "Winable: " << eopi::arrays::is_boardgame_winable(winable)
         << " Not Winable: " << eopi::arrays::is_boardgame_winable(not_winable)
         << endl;

    cout << "Removing 0 from:\n";
    print(winable);
    auto new_end = eopi::arrays::remove(winable.begin(), winable.end(), 0);
    winable.erase(new_end, winable.end());
    print(winable);

    vector<std::uint32_t> unique_input = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    print(unique_input);
    cout << "After unique\n";
    auto new_end_unique =
        eopi::arrays::unique(unique_input.begin(), unique_input.end());
    unique_input.erase(new_end_unique, unique_input.end());
    print(unique_input);

    vector<std::int32_t> missing_int = {-1, 1, 3, 2, 4, -1, 9, 0};
    print(missing_int);
    cout << "Missing in ^ is: "
         << eopi::arrays::smallest_missing_positive(missing_int) << endl;

    vector<std::int32_t> heights = {-1, 4, 3, 2, -2, 2, 3, 0, -1, -2};
    print(heights);
    cout << "Traversing heights requires a robot with capacity: "
         << eopi::arrays::max_difference(heights) << endl;

    cout << "Maximum profit for two buys would be: "
         << eopi::arrays::max_difference_twice(heights) << endl;
    cout << "Maximum profit for infinite buys would be: "
         << eopi::arrays::max_difference_infinite(heights) << endl;
    cout << "Using max_k(2): " << eopi::arrays::max_difference(heights, 2)
         << endl;
    cout << "Using max_k(3): " << eopi::arrays::max_difference(heights, 3)
         << endl;

    vector<std::int32_t> zero = {-1,0,-3,0,-4};
    vector<std::int32_t> negatives_zero = {-1,0,-3,-4,5};
    cout << "Expecting: 0 -- " << eopi::arrays::max_product_all_but_one(zero) << " " << eopi::arrays::max_product_all_but_one(negatives_zero) << endl;

    vector<std::int32_t> negative = {-1,-2,-3,-4,-5,-6};
    cout << "Expecting; -120 -- " << eopi::arrays::max_product_all_but_one(negative) << endl;

    vector<std::int32_t> single_zero = {0,1,2,3,4,5};
    cout << "Expecting; 120 -- " << eopi::arrays::max_product_all_but_one(single_zero) << endl;

    vector<std::int32_t> sequence = {0,1,2,1,2,3,0,4,2,3,4,5,6};
    print(sequence);
    auto sub_array = eopi::arrays::max_increasing_subarray(sequence);
    cout << "Longest increasing sub-array: " << sub_array.first << " " << sub_array.second << std::endl;

    cout << "Primes until 100:\n";
    print(eopi::arrays::euler_sieve(100));
    print(eopi::arrays::euler_sieve(11));

    vector<int32_t> permuted = {0,1,2,3,4,5,6,7,8,9};
    vector<int32_t> permuter = {1,2,4,7,6,5,0,3,9,8};

    cout << "Applying to X, permutation Y, to result Z:\n";
    print(permuted);
    print(permuter);
    permuted = eopi::arrays::apply_permutation(std::move(permuted),permuter);
    print(permuted);

    vector<int32_t> rotated = {0,1,2,3,4,5,6,7,8,9};
    print(rotated);
    cout << "Rotating by 5:\n";
    rotated = eopi::arrays::rotate(std::move(rotated),5);
    print(rotated);
    return 0;
}
