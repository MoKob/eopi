#ifndef EOPI_TREES_BINARY_TREE_HPP_
#define EOPI_TREES_BINARY_TREE_HPP_

#include <cstdint>
#include <memory>
#include <utility>

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

template <typename Payload>
std::shared_ptr<BinaryTreeNode<Payload>>
make_node(Payload const &data,
          std::shared_ptr<BinaryTreeNode<Payload>> left = nullptr,
          std::shared_ptr<BinaryTreeNode<Payload>> right = nullptr) {
  return std::make_shared<BinaryTreeNode<Payload>>(data, left, right);
}

} // namespace trees
} // namespace eopi

#endif // EOPI_TREES_BINARY_TREE_HPP_
