#include <iomanip>
#include <iostream>

#include <vector>

#include "algorithms.hpp"
#include "bigint.hpp"
#include "randoms.hpp"

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


    return 0;
}
