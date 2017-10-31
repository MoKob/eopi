#ifndef EOPI_LISTS_LINKED_LIST_HPP_
#define EOPI_LISTS_LINKED_LIST_HPP_

#include <algorithm>
#include <cassert>
#include <memory>
#include <tuple>
#include <vector>

#include <iostream>

namespace eopi {
namespace lists {

template <typename Payload> struct ListNode {
  Payload data;
  std::shared_ptr<ListNode<Payload>> next;

  ListNode(Payload data, std::shared_ptr<ListNode<Payload>> next)
      : data(std::move(data)), next(std::move(next)) {}
};

namespace tool {
// create a list from a vector
template <typename Payload>
std::shared_ptr<ListNode<Payload>>
from_vector(std::vector<Payload> const &vec) {
  if (vec.empty())
    return nullptr;

  std::shared_ptr<ListNode<Payload>> head =
      std::make_shared<ListNode<Payload>>(vec.front(), nullptr);

  auto cur = head;

  std::for_each(vec.begin() + 1, vec.end(), [&cur](auto const &data) {
    cur->next = std::make_shared<ListNode<Payload>>(data, nullptr);
    cur = cur->next;
  });

  return head;
}

// convert back to vector
template <typename Payload>
std::vector<Payload> to_vector(std::shared_ptr<ListNode<Payload>> list) {
  std::vector<Payload> vec;
  while (list) {
    vec.push_back(list->data);
    list = list->next;
  }
  return vec;
}

// get the k-th element from a list
template <typename Payload>
std::shared_ptr<ListNode<Payload>> get(std::shared_ptr<ListNode<Payload>> list,
                                       std::uint32_t k) {
  while (k-- && list)
    list = list->next;
  return list;
}
} // namespace tool

namespace algorithm {

// merge two sorted lists into a single linked list
template <typename Payload>
std::shared_ptr<ListNode<Payload>>
merge(std::shared_ptr<ListNode<Payload>> lhs,
      std::shared_ptr<ListNode<Payload>> rhs) {
  assert(lhs && rhs);

  // the new head of the list will be the minimum of lhs.data/rhs.data
  std::shared_ptr<ListNode<Payload>> head;
  if (lhs->data < rhs->data) {
    head = lhs;
    lhs = lhs->next;
  } else {
    head = rhs;
    rhs = rhs->next;
  }

  // current position in the list
  auto cur = head;
  // as long as we have two elements, connect head to the next element
  while (lhs && rhs) {
    if (lhs->data < rhs->data) {
      cur->next = lhs;
      lhs = lhs->next;
    } else {
      cur->next = rhs;
      rhs = rhs->next;
    }
    cur = cur->next;
  }

  // append the rest of the list
  if (lhs)
    cur->next = lhs;
  else
    cur->next = rhs;

  return head;
}

// reverse the content of a list
template <typename Payload>
std::shared_ptr<ListNode<Payload>>
reverse(std::shared_ptr<ListNode<Payload>> head) {
  // starting of with the new end of the list
  std::shared_ptr<ListNode<Payload>> last = nullptr;

  while (head->next) {
    auto next = head->next;
    head->next = last;
    last = head;
    head = next;
  }

  head->next = last;

  // the tail is the new head
  return head;
}

// reverse a list in batches. Will only invert complete batches
template <typename Payload>
std::shared_ptr<ListNode<Payload>>
reverse(std::shared_ptr<ListNode<Payload>> head,
        std::uint32_t const batch_size) {
  std::shared_ptr<ListNode<Payload>> tail = nullptr, result = head;

  auto batch_start = head;
  do {
    auto batch_last = batch_start;
    std::uint32_t current_size = 0;
    while (batch_last && current_size + 1 < batch_size)
      current_size++, batch_last = batch_last->next;

    // do not reverse incomplete batches
    if (current_size + 1 != batch_size)
      return result;

    // remember the
    auto tmp = batch_last->next;
    batch_last->next = nullptr;

    // reverse and splice back in
    if (tail)
      tail->next = reverse(batch_start);
    else
      result = reverse(batch_start);

    // splice back in
    batch_start->next = tmp;
    tail = batch_start;
    batch_start = tmp;
  } while (batch_start);

  return result;
}

// Find the first common node of two non-cyclic lists. Returns null, if no such
// node exists
template <typename Payload>
std::shared_ptr<ListNode<Payload>>
find_first_shared(std::shared_ptr<ListNode<Payload>> const lhs,
                  std::shared_ptr<ListNode<Payload>> const rhs) {
  auto const find_tail_and_length = [](auto head) {
    std::size_t count = 1;
    while (head->next)
      ++count, head = head->next;
    return std::make_pair(count, head);
  };

  std::size_t size_lhs, size_rhs;
  std::shared_ptr<ListNode<Payload>> tail_lhs, tail_rhs;

  std::tie(size_lhs, tail_lhs) = find_tail_and_length(lhs);
  std::tie(size_rhs, tail_rhs) = find_tail_and_length(rhs);

  // two lists with a common node share a common tail
  if (tail_lhs != tail_rhs)
    return nullptr;

  // common tail, the first common node is at least min(size_lhs,size_rhs)
  // from the end. Move the longer list ahead, so we are at the same distance
  // from the end to the left and to the right

  auto share_lhs = lhs;
  auto share_rhs = rhs;

  while (size_lhs > size_rhs)
    --size_lhs, share_lhs = share_lhs->next;

  while (size_rhs > size_lhs)
    --size_rhs, share_rhs = share_rhs->next;

  while (share_lhs != share_rhs)
    share_lhs = share_lhs->next, share_rhs = share_rhs->next;

  return share_lhs;
}

// check for cyclic pointers in a list, using no additional space
template <typename Payload>
bool is_cyclic(std::shared_ptr<ListNode<Payload>> list) {
  auto quick = list;
  auto slow = list;
  while (quick) {
    quick = quick->next;
    if (quick)
      quick = quick->next;

    slow = slow->next;

    if (quick == slow)
      return true;
  }
  // reached the end of the list
  return false;
}

// remove an element from the list which is not last.
template <typename Payload>
std::shared_ptr<ListNode<Payload>>
remove(std::shared_ptr<ListNode<Payload>> list) {
  // we can only remove elemnts which are not last
  if (list->next == nullptr)
    return list;

  list->data = list->next->data;
  list->next = list->next->next;

  return list;
}

template <typename Payload>
std::shared_ptr<ListNode<Payload>>
remove_after(std::shared_ptr<ListNode<Payload>> list) {
  // we can only remove elemnts which are not last
  if (list->next == nullptr)
    return list;

  list->next = list->next->next;

  return list;
}

// remove the k to last element from a list, since the element can be the head,
// the function returns the new head. Will remove head if k > |list|
template <typename Payload>
std::shared_ptr<ListNode<Payload>>
remove(std::shared_ptr<ListNode<Payload>> head, std::uint32_t k) {
  auto delta = tool::get(head, k + 1);
  // we are in a list that isn't k in size
  if (!delta) {
    return remove(head);
  }

  auto pre_remove = head;
  // skip ahead, til the end of the list
  while (delta) {
    delta = delta->next;
    pre_remove = pre_remove->next;
  }
  remove_after(pre_remove);

  return head;
}

template <typename Payload>
void unique(std::shared_ptr<ListNode<Payload>> head) {
  // as long as there are next elements, we either remove the following item (if
  // it is the same as head) or advance to a new unique element
  while (head->next) {
    if (head->next->data == head->data)
      head->next = head->next->next;
    else
      head = head->next;
  }
}

// all even-index elements followed by all odd-index elements
template <typename Payload>
std::shared_ptr<ListNode<Payload>>
even_odd(std::shared_ptr<ListNode<Payload>> head) {
  // require at least two elements
  if (!head->next)
    return head;
  auto even = head, odd = even->next, odd_head = even->next;
  while (odd && odd->next) {
    even->next = odd->next;
    even = even->next;
    odd->next = even->next;
    odd = odd->next;
  }
  // connect the odd list to the even-list
  even->next = odd_head;
  return head;
}

template <typename Payload>
std::shared_ptr<ListNode<Payload>>
interleave(std::shared_ptr<ListNode<Payload>> lhs,
           std::shared_ptr<ListNode<Payload>> rhs) {
  auto ret = lhs;

  auto cur = lhs;
  lhs = lhs->next;

  while (lhs && rhs) {
    cur->next = rhs;
    rhs = rhs->next;
    cur = cur->next;
    cur->next = lhs;
    lhs = lhs->next;
    cur = cur->next;
  }

  if (lhs)
    cur->next = lhs;

  if (rhs)
    cur->next = rhs;

  return ret;
}

template <typename Payload>
std::shared_ptr<ListNode<Payload>>
zip(std::shared_ptr<ListNode<Payload>> head) {
  // find the middle entry (O(N)):
  auto fast = head, mid = head;
  while (fast) {
    fast = fast->next;
    if (fast)
      fast = fast->next;
    mid = mid->next;
  }

  auto tmp = mid;
  mid = mid->next;
  tmp->next = nullptr;

  // reverse the second part of the list
  mid = reverse(mid);

  // merge both lists for the final result
  return interleave(head, mid);
}

} // namespace algorithm

} // namespace lists
} // namespace eopi

#endif // EOPI_LISTS_LINKED_LIST_HPP_
