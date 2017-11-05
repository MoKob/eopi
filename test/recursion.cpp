#include <iostream>
#include <string>

#include "recursion/algorithms.hpp"

using namespace std;

int main() {
  eopi::recursion::algorithms::hanoi(4);
  {
    // esre matching
    {
      string text = "xyaW9123";
      string ex1 = "^aW9$";
      string ex2 = "^aW9";
      string ex3 = "aW9$";
      string ex4 = "aW9";
      cout << "Matching \"" << text << "\" with \"" << ex1 << "\" yields: "
           << eopi::recursion::algorithms::esre_match(text, ex1) << endl;
      cout << "Matching \"" << text << "\" with \"" << ex2 << "\" yields: "
           << eopi::recursion::algorithms::esre_match(text, ex2) << endl;
      cout << "Matching \"" << text << "\" with \"" << ex3 << "\" yields: "
           << eopi::recursion::algorithms::esre_match(text, ex3) << endl;
      cout << "Matching \"" << text << "\" with \"" << ex4 << "\" yields: "
           << eopi::recursion::algorithms::esre_match(text, ex4) << endl;
    }
    {
      string text = "aw9999b";
      string ex1 = "aw9*b";
      cout << "Matching \"" << text << "\" with \"" << ex1 << "\" yields: "
           << eopi::recursion::algorithms::esre_match(text, ex1) << endl;
    }
    {
      string text = "awb";
      string ex1 = "aw9*b";
      cout << "Matching \"" << text << "\" with \"" << ex1 << "\" yields: "
           << eopi::recursion::algorithms::esre_match(text, ex1) << endl;
    }
  }
}
