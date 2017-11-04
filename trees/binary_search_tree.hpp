#ifndef EOPI_TREES_BINARY_SEARCH_TREE_HPP_
#define EOPI_TREES_BINARY_SEARCH_TREE_HPP_

#include <memory>

namespace eopi {
namespace trees {

template <typename value_type> class BinarySearchTree;

template <typename value_type> class TreeNode {
  friend class BinarySearchTree<value_type>;

public:
  value_type const &operator*() const { return value; }
  TreeNode(value_type value) : value(value) {}

private:
  TreeNode<value_type> *find(value_type const key) {
    if (value < key) {
      return right ? right->find(key) : nullptr;
    } else if (value > key) {
      return left ? left->find(key) : nullptr;
    } else {
      if (left && left->value == key)
        return left->find(key);
      else
        return this;
    }
  }

  TreeNode<value_type> *insert(value_type const key) {
    auto const insert = [key](auto &child) {
      child = std::make_unique<TreeNode<value_type>>(key);
      return child.get();
    };

    if (key <= value) {
      if (left)
        return left->insert(key);
      else
        return insert(left);
    } else {
      if (right)
        return right->insert(key);
      else
        return insert(right);
    }
  }

  value_type value;
  std::unique_ptr<TreeNode<value_type>> left, right;
};

template <typename value_type> class BinarySearchTree {
private:
  using TreeNodeType = TreeNode<value_type>;

public:
  TreeNodeType *find(value_type key) {
    if (root)
      return root->find(key);
    else
      return nullptr;
  }
  TreeNodeType *insert(value_type key) {
    if (root)
      return root->insert(key);
    else {
      root = std::make_unique<TreeNodeType>(key);
      return root.get();
    }
  }

private:
  std::unique_ptr<TreeNodeType> root;
};

} // namespace trees
} // namespace eopi

#endif // EOPI_TREES_BINARY_SEARCH_TREE_HPP_
