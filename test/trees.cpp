#include "trees/binary_tree.hpp"

#include <iostream>

using namespace std;

int main() {
  { // basic tree functionality
    using eopi::trees::make_node;
    auto tree = make_node(
        'A',
        make_node('B',
                  make_node('C', make_node('D', make_node('E'), make_node('F')),
                            make_node('G')),
                  make_node('H', make_node('I'), make_node('J'))),
        make_node('K', make_node('L', make_node('M'), make_node('N')),
                  make_node('O')));

    cout << "Tree Height: " << tree->height() << endl;
    cout << "Balanced: " << tree->balanced() << endl;
  }

  { // k-unbalanced
    using eopi::trees::make_node;
    std::shared_ptr<eopi::trees::BinaryTreeNode<int>> null;
    auto tree = make_node(
        314, make_node(6, make_node(271, make_node(28), make_node(0)),
                       make_node(561, null, make_node(3, make_node(17)))),
        make_node(6, make_node(2, null, make_node(1, make_node(401, null,
                                                               make_node(641)),
                                                  make_node(257))),
                  make_node(271, null, make_node(28))));
    auto unbalanced = eopi::trees::get_unbalanced(tree, 3);
    cout << "K-unbalanced at: " << unbalanced->data << endl;
  }
}
