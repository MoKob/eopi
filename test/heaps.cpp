#include "heaps/algorithms.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  {
    vector<int32_t> code{200, 300, 400, 100};
    cout << "Expecting: 7, Got: " << eopi::heaps::algorithms::bonusses(code)
         << endl;
  }
  {
    eopi::heaps::algorithms::RunningMedian median;
    for (int i = 0; i < 20; ++i) {
      auto val = rand() % 20;
      cout << "Adding " << val;
      median.emplace(val);
      cout << " - Median: " << median.median() << endl;
    }
  }
  {
    vector<int> heap(20);
    iota(heap.begin(), heap.end(), 0);
    random_shuffle(heap.begin(), heap.end());
    make_heap(heap.begin(), heap.end());
    cout << "Heap:";
    for (auto h : heap)
      cout << " " << h;
    cout << endl;

    cout << "Compare 5th largest element to 10: "
         << eopi::heaps::algorithms::compare(heap, 5, 10) << endl;
    cout << "Compare 11th largest element to 10: "
         << eopi::heaps::algorithms::compare(heap, 11, 10) << endl;
    cout << "Compare 10th largest element to 10: "
         << eopi::heaps::algorithms::compare(heap, 10, 10) << endl;
  }
}
