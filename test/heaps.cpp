#include "heaps/algorithms.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  {
    vector<std::int32_t> code{200, 300, 400, 100};
    cout << "Expecting: 7, Got: " << eopi::heaps::algorithms::bonusses(code)
         << endl;
  }
}
