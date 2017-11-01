#ifndef EOPI_STACKS_MAX_STACK_HPP
#define EOPI_STACKS_MAX_STACK_HPP

#include <cstddef>
#include <vector>

namespace eopi {
namespace stacks {
template <typename T> class max_stack {
public:
  typedef T value_type;

  // find the maximum of all elements in the stack
  value_type const &max() const { return values[max_ptrs.back()]; }

  // add a new element
  void push(value_type &&value) {
    values.emplace_back(value);
    if (max_ptrs.empty() || values[max_ptrs.back()] < values.back())
      max_ptrs.push_back(values.size() - 1);
  }

  bool empty() const { return values.empty(); }

  value_type const &top() const { return values.back(); }

  value_type pop() {
    if (max_ptrs.back() + 1 >= values.size())
      max_ptrs.pop_back();
    auto value = values.back();
    values.pop_back();
    return value;
  }

private:
  // the elements of the stack
  std::vector<value_type> values;
  // pointers to the remaining max-elements of the stack
  std::vector<std::size_t> max_ptrs;
};
} // namespace stacks
} // namespace eopi

#endif // EOPI_STACKS_MAX_STACK_HPP
