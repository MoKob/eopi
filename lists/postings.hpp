#include <iostream>
#include <memory>
#include <vector>

namespace eopi {
namespace lists {
namespace postings {

template <typename Payload> struct ListNode {
  Payload data;
  std::shared_ptr<ListNode<Payload>> next;
  std::shared_ptr<ListNode<Payload>> post;

  ListNode(Payload data, std::shared_ptr<ListNode<Payload>> next = nullptr,
           std::shared_ptr<ListNode<Payload>> post = nullptr)
      : data(std::move(data)), next(std::move(next)), post(std::move(post)) {}
};

namespace tool {
template <typename Payload>
std::shared_ptr<ListNode<Payload>>
generate_random_posts(std::vector<Payload> const &data) {
  // do we have data?
  if (data.empty())
    return nullptr;

  std::vector<std::shared_ptr<ListNode<Payload>>> list;
  for (auto const &payload : data)
    list.push_back(std::make_shared<ListNode<Payload>>(payload));

  for (std::size_t i = 0; i + 1 < list.size(); ++i)
    list[i]->next = list[i + 1];

  for (std::size_t i = 0; i < list.size(); ++i)
    list[i]->post = list[rand() % list.size()];

  return list.front();
}

// print a non-cyclic postings list
template <typename Payload>
void print_post(std::shared_ptr<ListNode<Payload>> head) {
  std::cout << "Post:";
  while (head != nullptr) {
    std::cout << " [" << head.get() << ": " << head->data << ", "
              << head->post->data << "]";
    head = head->next;
  }
  std::cout << std::endl;
}
} // namespace tool

namespace algorithm {

// copy a non-cyclic postings list
template <typename Payload>
std::shared_ptr<ListNode<Payload>>
copy(std::shared_ptr<ListNode<Payload>> head) {
  // splice in new elements that are copies of the previous element
  auto cur = head;
  while (cur != nullptr) {
    auto cur_copy = std::make_shared<ListNode<Payload>>(cur->data, cur->next);
    cur->next = cur_copy;
    cur = cur_copy->next;
  }

  // for every second element, set the posting element, list has 2*n elements
  cur = head;
  while (cur != nullptr) {
    cur->next->post = cur->post->next;
    cur = cur->next->next;
  }

  // now separate the two lists again, keeping every second element around
  auto copy_head = head->next;

  cur = head;
  auto cur_copy = head->next;
  while (cur != nullptr) {
    cur->next = cur_copy->next;
    cur = cur->next;
    if (cur) {
      cur_copy->next = cur->next;
      cur_copy = cur_copy->next;
    }
  }

  return copy_head;
}

} // namespace algorithm

} // namespace postings
} // namespace lists
} // namespace eopi
