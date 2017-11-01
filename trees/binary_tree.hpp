#ifndef EOPI_TREES_BINARY_TREE_HPP_
#define EOPI_TREES_BINARY_TREE_HPP_

#include <cstdint>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

namespace eopi {
namespace trees {
template <typename Payload> class BinaryTreeNode {
public:
  // alias for easier code
  typedef std::shared_ptr<BinaryTreeNode<Payload>> NodePtr;

  // constructor
  BinaryTreeNode(Payload data, NodePtr left = nullptr, NodePtr right = nullptr)
      : data(data), left(std::move(left)), right(std::move(right)) {}

  // compute the height (recursively) of the (sub)-tree
  std::uint32_t height() const {
    std::uint32_t lft = 0, rgt = 0;
    if (left)
      lft = left->height();
    if (right)
      rgt = right->height();
    return std::max(lft, rgt) + 1;
  }

  Payload data;
  NodePtr left, right;

  bool balanced() const { return balanced_height().first; }

private:
  std::pair<bool, std::uint32_t> balanced_height() const {
    std::pair<bool, std::uint32_t> lft = {true, 1}, rgt = {true, 1};
    if (left)
      return lft = left->balanced_height();

    if (right)
      return rgt = right->balanced_height();

    return {std::abs(lft.first - rgt.first) < 1,
            std::max(lft.second, rgt.second) + 1};
  }
};

namespace detail {
template <typename Payload>
std::pair<std::shared_ptr<BinaryTreeNode<Payload>>, std::int32_t>
unbalanced_internal(std::shared_ptr<BinaryTreeNode<Payload>> node,
                    std::int32_t k) {
  typedef std::shared_ptr<BinaryTreeNode<Payload>> NodePtr;
  std::pair<NodePtr, std::int32_t> left = {nullptr, 0}, right = {nullptr, 0};

  if (node->left)
    left = unbalanced_internal(node->left, k);

  if (left.first)
    return left;

  if (node->right)
    right = unbalanced_internal(node->right, k);

  if (right.first)
    return right;

  // both left/right are k-balanced
  if (std::abs(left.second - right.second) <= k) {
    // still balanced, return the size of the tree
    return {nullptr, left.second + right.second + 1};
  } else {
    // successfully identified a node
    return {node, 0};
  }
}

} // namespace detail

// find a node whose balances to left/right are larger than k, but all
// elements below are k-balanced
template <typename Payload>
std::shared_ptr<BinaryTreeNode<Payload>>
get_unbalanced(std::shared_ptr<BinaryTreeNode<Payload>> root,
               std::uint32_t const k) {
  return detail::unbalanced_internal(root, k).first;
}

// check if one tree is a mirror of the other
template <typename Payload>
bool are_mirrored(std::shared_ptr<BinaryTreeNode<Payload>> lhs,
                  std::shared_ptr<BinaryTreeNode<Payload>> rhs) {
  // only one present
  if (!lhs ^ !rhs)
    return false;

  // both not present, as a base case
  if (!lhs && !rhs)
    return true;

  if (lhs->data != rhs->data)
    return false;

  // if both subtrees are mirrored too, we are good
  return are_mirrored(lhs->right, rhs->left) &&
         are_mirrored(lhs->left, rhs->right);
}

// check if a tree is symmetric
template <typename Payload>
bool symmetric(std::shared_ptr<BinaryTreeNode<Payload>> root) {
  return are_mirrored(root->left, root->right);
}

// call functor on tree nodes in pre-order
template <typename Payload, typename functor>
void pre_order(std::shared_ptr<BinaryTreeNode<Payload>> root, functor func) {
  std::stack<std::shared_ptr<BinaryTreeNode<Payload>>> stack;
  stack.push(root);

  // do pre-order traversal of the tree
  while (!stack.empty()) {
    auto cur = stack.top();
    stack.pop();
    func(cur);
    if (cur->right)
      stack.push(cur->right);
    if (cur->left)
      stack.push(cur->left);
  }
}

template <typename Payload, typename functor>
void post_order(std::shared_ptr<BinaryTreeNode<Payload>> root, functor func) {
  std::stack<std::shared_ptr<BinaryTreeNode<Payload>>> stack;
  stack.push(root);

  // do post-order traversal
  // initialise previous vertex to null
  std::shared_ptr<BinaryTreeNode<Payload>> prev = nullptr;
  while (!stack.empty()) {
    auto cur = stack.top();
    // at a leaf node, output
    if (!cur->left && !cur->right) {
      func(cur);
      stack.pop();
    } else {
      // either coming from the right or from the only child
      if (prev == cur->right || (cur->right == nullptr && prev == cur->left)) {
        // backtracking up the call-stack, call functor
        func(cur);
        stack.pop();
      }
      // coming from the top
      else if (prev != cur->left) {
        if (cur->right)
          stack.push(cur->right);
        if (cur->left)
          stack.push(cur->left);
      }
      // else {
      // coming from the left. The right node is already on the stack.
      // }
    }
    prev = cur;
  }
}

template <typename Payload>
std::shared_ptr<BinaryTreeNode<Payload>>
make_node(Payload const &data,
          std::shared_ptr<BinaryTreeNode<Payload>> left = nullptr,
          std::shared_ptr<BinaryTreeNode<Payload>> right = nullptr) {
  return std::make_shared<BinaryTreeNode<Payload>>(data, left, right);
}

// construct a binary tree from a given pre and in-order traversal
template <typename Payload>
std::shared_ptr<BinaryTreeNode<Payload>>
build_tree(std::vector<Payload> const &pre_order,
           std::vector<Payload> const &in_order) {
  if (pre_order.empty() || pre_order.size() != in_order.size())
    return nullptr;

  std::shared_ptr<BinaryTreeNode<Payload>> tree = make_node(pre_order[0]);
  std::stack<std::shared_ptr<BinaryTreeNode<Payload>>> stack;
  stack.push(tree);
  std::size_t io = 0, po = 0;

  auto const left = [&]() {
    po++;
    if (po < pre_order.size()) {
      stack.top()->left = make_node(pre_order[po]);
      stack.push(stack.top()->left);
    }
  };

  auto const right = [&]() {
    po++;
    auto cur = stack.top();
    stack.pop();
    if (po < pre_order.size()) {
      cur->right = make_node(pre_order[po]);
      stack.push(cur->right);
    }
  };

  // loop over all elements
  while (po < pre_order.size()) {
    // middle of a tree (current root)
    if (in_order[io] == stack.top()->data) {
      right();
    } else {
      left();
    }
  }

  stack.push(tree);
  return tree;
}

} // namespace trees
} // namespace eopi

#endif // EOPI_TREES_BINARY_TREE_HPP_
