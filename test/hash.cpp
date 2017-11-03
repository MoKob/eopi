#include "hash/algorithms.hpp"

#include <string>
#include <vector>

using namespace std;

int main() {

  { // list all anagrams of a given set of strings
    vector<string> values = {"debitcard", "elvis",   "silent", "badcredit",
                             "lives",     "freedom", "listen", "levis"};

    eopi::hash::algorithms::list_anagrams(values);
  }
}
