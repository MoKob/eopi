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
        : data(std::move(data)), next(std::move(next)) {}
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

    std::for_each(vec.begin() + 1, vec.end(), [&cur](auto const& data) {
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

// reverse the content of a list
template <typename Payload>
std::shared_ptr<ListNode<Payload>> reverse(
    std::shared_ptr<ListNode<Payload>> head) {
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

template <typename Payload>
std::shared_ptr<ListNode<Payload>> reverse(
    std::shared_ptr<ListNode<Payload>> head, std::uint32_t const batch_size) {
    std::shared_ptr<ListNode<Payload>> tail = nullptr, result = head;

    auto batch_start = head;
    do
    {
        auto batch_last = batch_start;
        std::uint32_t current_size = 0;
        while( batch_last && current_size + 1 < batch_size )
            current_size++, batch_last = batch_last->next;

        // do not reverse incomplete batches
        if( current_size + 1 != batch_size )
            return result;

        // remember the 
        auto tmp = batch_last->next;
        batch_last->next = nullptr;

        // reverse and splice back in
        if(tail) tail->next = 
            reverse(batch_start);
        else
            result = reverse(batch_start);

        // splice back in
        batch_start->next = tmp;
        tail = batch_start;
        batch_start = tmp;
    } while (batch_start);

    return result;
}

// check for cyclic pointers in a list, using no additional space
template <typename Payload>
bool is_cyclic(std::shared_ptr<ListNode<Payload>> list) {
    auto quick = list;
    auto slow = list;
    while (quick) {
        quick = quick->next;
        if (quick) quick = quick->next;

        slow = slow->next;

        if (quick == slow) return true;
    }
    // reached the end of the list
    return false;
}

}  // namespace algorithm

}  // namespace lists
}  // namespace eopi

#endif  // EOPI_LISTS_LINKED_LIST_HPP_
