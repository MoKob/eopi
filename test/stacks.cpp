#include "stacks/algorithms.hpp"
#include "stacks/max_stack.hpp"

#include <iostream>
#include <string>

using namespace std;

int main() {
  {
    eopi::stacks::max_stack<int> stack;
    for (int i = 0; i < 10; ++i) {
      stack.push(rand() % 100);
      cout << "Added:  " << stack.top() << " Current Max: " << stack.max()
           << endl;
    }
    for (int i = 0; i < 10; ++i) {
      cout << "Popping from: " << stack.top() << " Current Max: " << stack.max()
           << endl;
      stack.pop();
    }
  }

  {
    string braces = "((())()(()(";
    cout << "Max valid in: " << braces << ": "
         << eopi::stacks::algorithms::maximum_valid_bracket_substring(braces)
         << endl;
  }
}
