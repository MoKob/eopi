#include <iostream>

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
}
