#ifndef EOPI_TREES_BINARY_SEARCH_TREE_HPP_
#define EOPI_TREES_BINARY_SEARCH_TREE_HPP_

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stack>
#include <tuple>
#include <vector>

namespace eopi {
namespace trees {

template <typename value_type> class BinarySearchTree;
template <typename value_type> class BinarySearchTreeFactory;

template <typename value_type> class TreeNode {
  friend class BinarySearchTree<value_type>;
  friend class BinarySearchTreeFactory<value_type>;

public:
  value_type const &operator*() const { return value; }
  TreeNode(value_type value) : value(value) {}

private:
  TreeNode<value_type> const *find(value_type const key) const {
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

  TreeNode<value_type> const *insert(value_type const key) {
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

  TreeNode<value_type> const *
  upper_bound(value_type const key,
              TreeNode<value_type> const *const last_larger) const {
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
  TreeNode<value_type> const *lca(TreeNode<value_type> const *const lhs,
                                  TreeNode<value_type> const *const rhs) const {
    if (((lhs->value < value) != (rhs->value < value)) || lhs->value == value ||
        rhs->value == value)
      return this;
    if (lhs->value < value)
      return left->lca(lhs, rhs);
    else
      return right->lca(lhs, rhs);
  }

  void print() const {
    std::cout << "[" << this << "]: " << value
              << " Left: " << (left ? left.get() : 0)
              << " Right: " << (right ? right.get() : 0) << std::endl;
    if (left)
      left->print();
    if (right)
      right->print();
  }

  value_type value;
  std::unique_ptr<TreeNode<value_type>> left, right;
};

template <typename value_type> class BinarySearchTree {
private:
  using TreeNodeType = TreeNode<value_type>;

public:
  TreeNodeType const *find(value_type key) const {
    if (root)
      return root->find(key);
    else
      return nullptr;
  }

  TreeNodeType const *insert(value_type key) {
    if (root)
      return root->insert(key);
    else {
      root = std::make_unique<TreeNodeType>(key);
      return root.get();
    }
  }

  TreeNodeType const *upper_bound(value_type key) const {
    if (root)
      return root->upper_bound(key, nullptr);
    else
      return nullptr;
  }

  // find the lowest common ancestor of a tree with unique keys
  TreeNodeType const *lca(TreeNodeType const *const lhs,
                          TreeNodeType const *const rhs) const {
    if (root)
      return root->lca(lhs, rhs);
    else
      return nullptr;
  }

  void print() const {
    if (root)
      root->print();
  }

private:
  std::unique_ptr<TreeNodeType> root;

  friend class BinarySearchTreeFactory<value_type>;
};

template <typename value_type> class BinarySearchTreeFactory {
private:
  template <typename iterator_type>
  static std::unique_ptr<TreeNode<value_type>> insert(iterator_type const begin,
                                                      iterator_type const end) {
    if (begin == end)
      return nullptr;

    auto middle = std::distance(begin, end) / 2;
    iterator_type middle_itr = begin;
    std::advance(middle_itr, middle);
    auto root = std::make_unique<TreeNode<value_type>>(*middle_itr);
    root->left = insert(begin, middle_itr);
    root->right = insert(middle_itr + 1, end);
    return root;
  }

public:
  // construct a balanced binary search tree from in-order (sorted) array
  static BinarySearchTree<value_type>
  in_order(std::vector<value_type> const &order) {
    BinarySearchTree<value_type> tree;
    if (order.empty())
      return tree;
    tree.root = insert(order.begin(), order.end());
    return tree;
  }

  // construct a search tree representing the pre-order traversal
  static BinarySearchTree<value_type>
  pre_order(std::vector<value_type> const &order) {
    BinarySearchTree<value_type> tree;
    if (order.empty())
      return tree;
    tree.root = std::make_unique<TreeNode<value_type>>(order.front());
    std::stack<TreeNode<value_type> *> path;
    path.push(tree.root.get());
    for (std::size_t i = 1; i < order.size(); ++i) {
      if (order[i] <= path.top()->value) {
        path.top()->left = std::make_unique<TreeNode<value_type>>(order[i]);
        path.push(path.top()->left.get());
      } else {
        auto cur = path.top();
        path.pop();
        while (!path.empty() && path.top()->value < order[i]) {
          cur = path.top();
          path.pop();
        }
        cur->right = std::make_unique<TreeNode<value_type>>(order[i]);
        path.push(cur->right.get());
      }
    }
    return tree;
  }
};

} // namespace trees
} // namespace eopi

#endif // EOPI_TREES_BINARY_SEARCH_TREE_HPP_
