#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

#include "search/algorithms.hpp"

using namespace std;

int main() {
  {
    vector<int> data(20);
    iota(data.begin(), data.end(), 0);

    auto lower_bound =
        eopi::search::algorithm::lower_bound(data.begin(), data.end(), 10);
    cout << "Found: " << *lower_bound << " when searching for 10" << endl;

    auto end =
        eopi::search::algorithm::lower_bound(data.begin(), data.end(), 21);
    cout << "Found: " << (end == data.end() ? "the end" : "some data")
         << " when looking for 21" << endl;

    auto end2 =
        eopi::search::algorithm::lower_bound(data.begin(), data.end(), -1);
    cout << "Found: " << (end2 == data.end() ? "the end" : "some data")
         << " when looking for -1" << endl;

    auto minus =
        eopi::search::algorithm::upper_bound(data.begin(), data.end(), -1);
    cout << "Found: " << *minus << " when searching for upper bound of -1"
         << endl;

    auto two =
        eopi::search::algorithm::upper_bound(data.begin(), data.end(), 2);
    cout << "Found: " << *two << " when searching for upper bound of 2" << endl;

    auto twenty =
        eopi::search::algorithm::upper_bound(data.begin(), data.end(), 20);
    cout << "Found: " << (twenty == data.end() ? "the end" : "some data")
         << " when looking for the upper bound of 20" << endl;
  }
  {
    vector<int> array = {-2, 0, 2, 3, 6, 7, 9};
    auto loc = eopi::search::algorithm::find_index_value_match(array);
    cout << "Values[" << loc << "] == " << array[loc] << endl;
  }
  {
    // identity array
    auto array =
        eopi::search::tool::make_array(137, [](auto const val) { return val; });

    cout << "Pos of " << 37 << " is: " << eopi::search::algorithm::find_unbound(
                                              array, static_cast<uint64_t>(37))
         << endl;

    cout << "Pos of " << 140
         << " is: " << (eopi::search::algorithm::find_unbound(
                            array, static_cast<uint64_t>(140)) ==
                                numeric_limits<size_t>::max()
                            ? "not found"
                            : " found, oh oh")
         << endl;
  }
  {
    // search two sorted arrays for the kth largest element
    vector<int32_t> lhs = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    vector<int32_t> rhs = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};

    cout << "The 17th element is: "
         << eopi::search::algorithm::kth_element_dual(17, lhs, rhs) << endl;
    cout << "The 0th element is: "
         << eopi::search::algorithm::kth_element_dual(0, lhs, rhs) << endl;
    cout << "The 1th element is: "
         << eopi::search::algorithm::kth_element_dual(1, lhs, rhs) << endl;
  }
  {
    // two-d search
    vector<vector<int>> field;
    field.push_back({-1, 2, 4, 4, 6});
    field.push_back({1, 5, 5, 9, 21});
    field.push_back({3, 6, 6, 9, 22});
    field.push_back({3, 6, 6, 8, 24});
    field.push_back({5, 8, 9, 12, 25});
    field.push_back({8, 10, 12, 13, 40});

    cout << "Field contains 7? : " << eopi::search::algorithm::find_2d(field, 7)
         << " 8: " << eopi::search::algorithm::find_2d(field, 8) << endl;
  }
  {
    // min max
    std::vector<int> data = {3, 2, 5, 1, 2, 4};
    auto min_max = eopi::search::algorithm::min_max(data);
    cout << "Min max are: " << min_max.first << " " << min_max.second
         << " (Elements: " << data[min_max.first] << " " << data[min_max.second]
         << ")" << std::endl;
  }
  {
    std::vector<int> data = {3, 2, 5, 1, 2, 4};
    auto second_smallest = eopi::search::algorithm::quick_select(2, data);
    cout << "Second smallest is: " << second_smallest << endl;
  }
  {
    std::vector<uint32_t> miss_dup = {1, 2, 4, 4, 5, 6};
    auto miss_dup_res =
        eopi::search::algorithm::missing_and_duplicate(miss_dup);
    cout << "Found: " << miss_dup_res.first << " to be missing and "
         << miss_dup_res.second << " to be present twice." << endl;
  }
  {
    std::vector<uint32_t> once = {3, 1, 3, 4, 3, 1, 1};
    cout << "once should be 4 and is: " << eopi::search::algorithm::once(once)
         << endl;
  }
}
