#ifndef EOPI_STACKS_MAX_QUEUE_HPP_
#define EOPI_STACKS_MAX_QUEUE_HPP_

#include "max_stack.hpp"
#include <stdexcept>

namespace eopi {
namespace stacks {

// a queue supporting a query for max-element
template <typename T> class max_queue {
public:
  typedef T value_type;

  void push(value_type &&value) { in.push(value); }
  void push(value_type const &value) { in.push(value); }

  void pop() {
    if (out.empty())
      transfer();

    out.pop();
  }

  value_type const &front() {
    if (out.empty())
      transfer();

    return out.top();
  }

  bool empty() { return in.empty() && out.empty(); }

  value_type const &max() {
    if (empty())
      throw std::out_of_range("Stack is empty");

    if (in.empty())
      return out.max();

    if (out.empty())
      return in.max();

    return in.max() < out.max() ? out.max() : in.max();
  }

private:
  // move values from the in to the out stack
  void transfer() {
    while (!in.empty()) {
      out.push(in.top());
      in.pop();
    }
  }

  max_stack<T> in;
  max_stack<T> out;
};

} // namespace stacks
} // namespace eopi

#endif // EOPI_STACKS_MAX_QUEUE_HPP_
