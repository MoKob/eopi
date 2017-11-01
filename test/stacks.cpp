#include "stacks/algorithms.hpp"
#include "stacks/max_queue.hpp"
#include "stacks/max_stack.hpp"

#include <iostream>
#include <stack>
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

  {
    std::stack<int> values;
    for (int i = 0; i < 10; i++)
      values.push(rand() % 100);

    eopi::stacks::algorithms::sort_descending(values);
    cout << "Sorted stack:";
    while (!values.empty()) {
      cout << " " << values.top();
      values.pop();
    }
    cout << endl;
  }

  {
    eopi::stacks::max_queue<int> que;
    for (std::int32_t i = 0; i < 20; ++i) {
      auto val = rand() % 100;
      que.push(std::move(val));
      cout << "Added: " << val << " Max: " << que.max() << std::endl;
    }
    for (std::int32_t i = 0; i < 20; ++i) {
      cout << "Next: " << que.front() << " Max: " << que.max() << std::endl;
      que.pop();
    }
  }
}
