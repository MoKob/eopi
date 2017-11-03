#include <algorithm>
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
  }
}
