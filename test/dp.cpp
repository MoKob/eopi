#include <cstdint>
#include <iostream>
#include <tuple>
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
  { cout << "Floors: " << eopi::dp::algorithms::critical_case(1, 15) << endl; }
  { cout << "Floors: " << eopi::dp::algorithms::critical_case(2, 15) << endl; }
  {
    vector<uint32_t> data = {25, 5,  10, 5,  10, 5,  10, 25,
                             1,  25, 1,  25, 1,  25, 5,  10};
    cout << "Max gain player 1: " << eopi::dp::algorithms::max_coin_gain(data)
         << endl;
  }
  {
    vector<int32_t> data = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9};
    auto lndss = eopi::dp::algorithms::longest_nondecreasing_subsequence(data);
    cout << "Sequence:";
    for (auto e : lndss)
      cout << " " << e;
    cout << endl;
  }
  {
    vector<vector<bool>> field = {{false, true, false, false, false},
                                  {false, true, false, true, true},
                                  {true, true, true, true, true},
                                  {false, true, true, true, false}};
    auto max_rect = eopi::dp::algorithms::max_subarray(field, false);
    auto max_square = eopi::dp::algorithms::max_subarray(field, true);

    cout << "Max Rect: (" << std::get<0>(max_rect) << ","
         << std::get<1>(max_rect) << ") - (" << std::get<2>(max_rect) << ","
         << std::get<3>(max_rect) << ")" << endl;
    cout << "Max Square: (" << std::get<0>(max_square) << ","
         << std::get<1>(max_square) << ") - (" << std::get<2>(max_square) << ","
         << std::get<3>(max_square) << ")" << endl;
  }
}
