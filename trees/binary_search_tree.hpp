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
      else {
        if (key == value)
          return this;
        else
          return insert(left);
      }
    } else {
      if (right)
        return right->insert(key);
      else
        return insert(right);
    }
  }

  TreeNode<value_type> *upper_bound(value_type const key,
                                    TreeNode<value_type> *last_larger) {
    if (key < value) {
      // remember the current node as minimum element larget than key
      if (left)
        return left->upper_bound(key, this);
      else
        return this;
    } else {
      // key >= value -> value > key only in right tree
      if (right)
        return right->upper_bound(key, last_larger);
      else
        return last_larger;
    }
  }

  // the lowest common ancester in a binary search tree with unique keys can be
  // computed by deciding if both nodes are to the left/right of a key. Only for
  // equal values, the decision cannot be made without exploring the subtree
  TreeNode<value_type> *lca(TreeNode<value_type> *lhs,
                            TreeNode<value_type> *rhs) {
    if (((lhs->value < value) != (rhs->value < value)) || lhs->value == value ||
        rhs->value == value)
      return this;
    if (lhs->value < value)
      return left->lca(lhs, rhs);
    else
      return right->lca(lhs, rhs);
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

  TreeNodeType *upper_bound(value_type key) {
    if (root)
      return root->upper_bound(key, nullptr);
    else
      return nullptr;
  }

  // find the lowest common ancestor of a tree with unique keys
  TreeNodeType *lca(TreeNodeType *lhs, TreeNodeType *rhs) {
    if (root)
      return root->lca(lhs, rhs);
    else
      return nullptr;
  }

private:
  std::unique_ptr<TreeNodeType> root;
};

} // namespace trees
} // namespace eopi

#endif // EOPI_TREES_BINARY_SEARCH_TREE_HPP_