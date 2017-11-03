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
  {
    string palindromic = "edified";
    cout << "Edified is palindromic permutable: "
         << eopi::hash::algorithms::has_palindromic_permutation(palindromic)
         << endl;
  }
  {
    vector<string> all_work = {"all",   "work", "and", "no",     "play",
                               "makes", "for",  "no",  "work",   "no",
                               "fun",   "and",  "no",  "results"};
    cout << "Closest repetition should be 2 and is: "
         << eopi::hash::algorithms::closest_repeated_pair(all_work) << endl;
  }
  { // compute the digest of a string in comparison to search-data
    vector<string> keywords = {"save", "union"};
    vector<string> text = {
        "my",      "paramount", "object",  "in",      "this",    "struggle",
        "is",      "to",        "save",    "the",     "union",   "and",
        "is",      "not",       "either",  "to",      "save",    "or",
        "destroy", "salvery",   "if",      "i",       "could",   "save",
        "the",     "union",     "without", "freeing", "any",     "slave",
        "i",       "would",     "do",      "it",      "and",     "if",
        "i",       "could",     "do",      "it",      "by",      "freeing",
        "all",     "slaves",    "i",       "would",   "do",      "it",
        "and",     "if",        "i",       "could",   "save",    "it",
        "by",      "freeing",   "some",    "and",     "leaving", "others",
        "alone",   "i",         "would",   "also",    "do",      "that"};

    auto range = eopi::hash::algorithms::digest(text, keywords);
    cout << "Range: " << range.first << " to " << range.second << " ("
         << range.second - range.first << "):";
    for (std::size_t i = range.first; i < range.second; ++i)
      cout << " " << text[i];
    cout << endl;
  }
}
