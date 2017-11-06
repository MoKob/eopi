#include <cstdint>
#include <iostream>
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
}
