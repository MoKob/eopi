#include <iostream>
#include <vector>

#include "trees/binary_search_tree.hpp"

using namespace std;

int main() {
  {
    eopi::trees::BinarySearchTree<int> tree;
    for (int i = 0; i < 10; ++i) {
      auto val = rand() % 20;
      cout << "Adding: " << val << " to the tree" << endl;
      tree.insert(val);
    }

    cout << "Contained elements:";
    for (int i = 0; i < 20; ++i) {
      auto itr = tree.upper_bound(i);
      cout << " " << i << ": " << (tree.find(i) == nullptr ? "no" : "yes")
           << " Upper bound: " << (itr ? *(*itr) : -1) << endl;
    }
  }
  { // create a perfect binary treei of the numbers 1-7
    eopi::trees::BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    tree.insert(2);
    tree.insert(3);
    tree.insert(1);

    cout << "In a perfect bst, the lca of 1,7 is: "
         << tree.lca(tree.find(1), tree.find(4))->operator*() << endl;
    cout << "In a perfect bst, the lca of 3,2 is: "
         << tree.lca(tree.find(3), tree.find(2))->operator*() << endl;
    cout << "In a perfect bst, the lca of 2,5 is: "
         << tree.lca(tree.find(5), tree.find(2))->operator*() << endl;
    cout << "In a perfect bst, the lca of 1,3 is: "
         << tree.lca(tree.find(1), tree.find(3))->operator*() << endl;
  }
  { // in a constructed tree:
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};
    auto const tree = eopi::trees::BinarySearchTreeFactory<int>::in_order(data);
    cout << "Redoing in a constructed tree (in-order)" << endl;
    cout << "In a perfect bst, the lca of 1,7 is: "
         << tree.lca(tree.find(1), tree.find(4))->operator*() << endl;
    cout << "In a perfect bst, the lca of 3,2 is: "
         << tree.lca(tree.find(3), tree.find(2))->operator*() << endl;
    cout << "In a perfect bst, the lca of 2,5 is: "
         << tree.lca(tree.find(5), tree.find(2))->operator*() << endl;
    cout << "In a perfect bst, the lca of 1,3 is: "
         << tree.lca(tree.find(1), tree.find(3))->operator*() << endl;
    tree.print();
  }
  {
    // construct a post-order tree
    std::vector<int> data = {19, 7,  3,  2,  5,  11, 17, 13,
                             43, 23, 37, 29, 31, 41, 47, 53};

    cout << "Tree in Figure 15.1" << endl;
    auto const tree =
        eopi::trees::BinarySearchTreeFactory<int>::pre_order(data);
    tree.print();
  }
  {
    std::vector<int> list_data = {2, 3, 5, 7, 11};
    auto tree = eopi::trees::BinarySearchTreeFactory<int>::list(list_data);
    tree.from_list();
    cout << "Constructed from sorted list via transformation" << endl;
    tree.print();

    cout << "Back into a list" << std::endl;
    tree.to_list();
    tree.print_list();
  }
}
