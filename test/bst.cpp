#include <iostream>

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
      cout << " " << i << ": " << (tree.find(i) == nullptr ? "no" : "yes")
           << endl;
    }
  }
}
