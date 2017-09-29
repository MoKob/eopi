#ifndef EOPI_LISTS_LINKED_LIST_HPP_
#define EOPI_LISTS_LINKED_LIST_HPP_

#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

#include <iostream>

namespace eopi {
namespace lists {

template <typename Payload>
struct ListNode {
    Payload data;
    std::shared_ptr<ListNode<Payload>> next;

    ListNode(Payload data, std::shared_ptr<ListNode<Payload>> next)
    : data(std::move(data)), next(std::move(next))
    {}
};

namespace tool {
// create a list from a vector
template <typename Payload>
std::shared_ptr<ListNode<Payload>> from_vector(
    std::vector<Payload> const& vec) {
    if (vec.empty()) return nullptr;

    std::shared_ptr<ListNode<Payload>> head =
        std::make_shared<ListNode<Payload>>(vec.front(), nullptr);

    auto cur = head;

    std::for_each(vec.begin()+1, vec.end(), [&cur](auto const& data) {
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
}  // namespace tool

namespace algorithm {

// merge two sorted lists into a single linked list
template <typename Payload>
std::shared_ptr<ListNode<Payload>> merge(
    std::shared_ptr<ListNode<Payload>> lhs,
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

}  // namespace algorithm

}  // namespace lists
}  // namespace eopi

#endif  // EOPI_LISTS_LINKED_LIST_HPP_
