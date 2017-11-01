#include "stacks/max_stack.hpp"

#include <iostream>

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
}
