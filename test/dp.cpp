#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

#include "dp/algorithms.hpp"

using namespace std;

int main() {
  {
    cout << "Can reach a score of 12 in : "
         << eopi::dp::algorithms::football_combinations(12) << " ways." << endl;
  }
  { // levensthein
    cout << "Tor and Tier are editable in: "
         << eopi::dp::algorithms::levenshtein_distance("Tor", "Tier") << endl;
  }
  {
    // fishing trip
    vector<vector<int32_t>> fish = {{0, 0, 1, 2, 0},
                                    {0, 1, 3, 0, 1},
                                    {0, 1, 2, 1, 2},
                                    {3, 0, 1, 0, 3},
                                    {2, 1, 4, 0, 3}};

    cout << "Max yield: " << eopi::dp::algorithms::fishing_trip(fish) << endl;
  }
  {
    vector<pair<uint32_t, uint32_t>> values = {{1, 5}, {5, 1}, {2, 3}};
    cout << "Knapsack: " << eopi::dp::algorithms::knapsack_zero_one(values, 8)
         << endl;
  }
  {
    vector<pair<uint32_t, uint32_t>> values = {
        {65, 20},  {35, 8},   {245, 60}, {195, 55}, {65, 40}, {150, 70},
        {275, 85}, {155, 25}, {120, 30}, {320, 65}, {75, 75}, {40, 10},
        {200, 95}, {100, 50}, {220, 40}, {99, 10}};
    cout << "Knapsack: " << eopi::dp::algorithms::knapsack_zero_one(values, 130)
         << endl;
  }
  {
    cout << "Measure: ";
    eopi::dp::algorithms::measure(2100, 2300);
  }
  {
    vector<int32_t> data = {904, 40, 523, 12, -335, -385, -124, 481, -31};
    cout << "Subset sum: "
         << eopi::dp::algorithms::max_subarray_sum_cyclic(data) << endl;
  }
}
