#ifndef EOPI_TREES_BINARY_SEARCH_TREE_HPP_
#define EOPI_TREES_BINARY_SEARCH_TREE_HPP_

#include <cmath>
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
      child = std::make_shared<TreeNode<value_type>>(key);
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

  // the lowest common ancester in a binary search tree with shared keys can be
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
  std::shared_ptr<TreeNode<value_type>> left, right;
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
      root = std::make_shared<TreeNodeType>(key);
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

  void print_list() const {
    std::cout << "[list]";
    if (root) {
      auto cur = root;
      do {
        std::cout << " (" << cur->operator*() << " : " << cur << ")";
        cur = cur->right;
      } while (cur != root);
    }
    std::cout << std::endl;
  }

  // transform a list form into a tree form
  void from_list() {
    // compute the length of the list
    std::size_t len = 1;
    auto cur = root->right;
    while (cur != root) {
      ++len;
      cur = cur->right;
    }
    // the first element of the next subtree
    auto next = root;
    root = from_list_helper(&next, 0, len);
  }

  // transform a tree form into a list form
  void to_list() {
    // O(n)
    auto begin_end = to_list_helper(root);

    // close off the list
    begin_end.first->left = begin_end.second;
    begin_end.second->right = begin_end.first;
    root = begin_end.first;
  }

private:
  std::shared_ptr<TreeNodeType> root;

  // returns the root of the new tree
  std::shared_ptr<TreeNodeType>
  from_list_helper(std::shared_ptr<TreeNodeType> *next, std::size_t begin,
                   std::size_t end) {
    if (begin >= end)
      return nullptr;

    auto middle = begin + (end - begin) / 2;
    auto left = from_list_helper(next, begin, middle);

    // the entry contained in next now is the root of the current tree
    auto local_root = *next;
    // set the subtree (or null, if child)
    local_root->left = left;

    // it's right subtree starts of to the right;
    *next = (*next)->right;
    local_root->right = from_list_helper(next, middle + 1, end);

    return local_root;
  }

  // returns the largest (last) node in the list
  std::pair<std::shared_ptr<TreeNodeType>, std::shared_ptr<TreeNodeType>>
  to_list_helper(std::shared_ptr<TreeNodeType> local_root) {
    // below a leaf
    if (local_root == nullptr)
      return {nullptr, nullptr};

    auto const connect = [](auto lhs, auto rhs) {
      if (lhs)
        lhs->right = rhs;
      if (rhs)
        rhs->left = lhs;
    };

    auto left = to_list_helper(local_root->left);
    auto right = to_list_helper(local_root->right);

    connect(left.second, local_root);
    connect(local_root, right.first);

    return {left.first ? left.first : local_root,
            right.second ? right.second : local_root};
  }

  friend class BinarySearchTreeFactory<value_type>;
};

template <typename value_type> class BinarySearchTreeFactory {
private:
  template <typename iterator_type>
  static std::shared_ptr<TreeNode<value_type>> insert(iterator_type const begin,
                                                      iterator_type const end) {
    if (begin == end)
      return nullptr;

    auto middle = std::distance(begin, end) / 2;
    iterator_type middle_itr = begin;
    std::advance(middle_itr, middle);
    auto root = std::make_shared<TreeNode<value_type>>(*middle_itr);
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
    tree.root = std::make_shared<TreeNode<value_type>>(order.front());
    std::stack<TreeNode<value_type> *> path;
    path.push(tree.root.get());
    for (std::size_t i = 1; i < order.size(); ++i) {
      if (order[i] <= path.top()->value) {
        path.top()->left = std::make_shared<TreeNode<value_type>>(order[i]);
        path.push(path.top()->left.get());
      } else {
        auto cur = path.top();
        path.pop();
        while (!path.empty() && path.top()->value < order[i]) {
          cur = path.top();
          path.pop();
        }
        cur->right = std::make_shared<TreeNode<value_type>>(order[i]);
        path.push(cur->right.get());
      }
    }
    return tree;
  }

  // interpreting a tree node in left->prev, right->next as doubly-linked list
  static BinarySearchTree<value_type>
  list(std::vector<value_type> const &values) {
    BinarySearchTree<value_type> tree;
    if (values.empty())
      return tree;

    tree.root = std::make_shared<TreeNode<value_type>>(values.front());
    auto cur = tree.root;
    for (std::size_t i = 1; i < values.size(); ++i) {
      cur->right = std::make_shared<TreeNode<value_type>>(values[i]);
      cur->right->left = cur;
      cur = cur->right;
    }
    tree.root->left = cur;
    cur->right = tree.root;
    return tree;
  }
};

} // namespace trees
} // namespace eopi

#endif // EOPI_TREES_BINARY_SEARCH_TREE_HPP_
