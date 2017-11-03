#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

#include "search/algorithms.hpp"

using namespace std;

int main() {
  {
    std::vector<int> data(20);
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
    std::vector<int> array = {-2, 0, 2, 3, 6, 7, 9};
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
                                std::numeric_limits<std::size_t>::max()
                            ? "not found"
                            : " found, oh oh")
         << endl;
  }
  {
    // search two sorted arrays for the kth largest element
    std::vector<std::int32_t> lhs = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    std::vector<std::int32_t> rhs = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};

    std::cout << "The 17th element is: "
              << eopi::search::algorithm::kth_element_dual(17, lhs, rhs)
              << std::endl;
    std::cout << "The 0th element is: "
              << eopi::search::algorithm::kth_element_dual(0, lhs, rhs)
              << std::endl;
    std::cout << "The 1th element is: "
              << eopi::search::algorithm::kth_element_dual(1, lhs, rhs)
              << std::endl;
  }
}
