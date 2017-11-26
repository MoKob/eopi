#include "trees/algorithms.hpp"
#include "trees/binary_tree.hpp"

#include <iostream>
#include <tuple>

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

  { // symmetrics
    using eopi::trees::make_node;
    std::shared_ptr<eopi::trees::BinaryTreeNode<int>> null;
    auto sym1 =
        make_node(314, make_node(6, null, make_node(2, null, make_node(3))),
                  make_node(6, make_node(2, make_node(3))));
    auto asym1 =
        make_node(314, make_node(6, null, make_node(561, null, make_node(3))),
                  make_node(6, make_node(2, make_node(1))));

    auto asym2 =
        make_node(314, make_node(6, null, make_node(561, null, make_node(3))),
                  make_node(6, make_node(561)));

    cout << "Symmetric: " << eopi::trees::symmetric(sym1)
         << " Asym: " << eopi::trees::symmetric(asym1) << " and "
         << eopi::trees::symmetric(asym2) << endl;

    cout << "Preorder Sym:";
    auto func = [](auto const node) { std::cout << " " << node->data; };
    eopi::trees::pre_order(sym1, func);
    cout << endl;
    cout << "Post-order:";
    eopi::trees::post_order(sym1, func);
    cout << endl;
  }

  { // build a tree
    vector<char> in_order = {'F', 'B', 'A', 'E', 'H', 'C', 'D', 'I', 'G'};
    vector<char> pre_order = {'H', 'B', 'F', 'E', 'A', 'C', 'D', 'G', 'I'};
    cout << "Pre-Order:";
    for (auto c : pre_order)
      cout << " " << c;
    cout << endl;
    auto tree = eopi::trees::build_tree(pre_order, in_order);
    cout << "Preorder of build:";
    auto func = [](auto const node) { std::cout << " " << node->data; };
    eopi::trees::pre_order(tree, func);
    cout << endl;
  }
  {
    // view from above
    vector<tuple<int, int, int, char>> ranges;
    ranges.emplace_back(std::make_tuple(0, 0, 4, 'A'));
    ranges.emplace_back(std::make_tuple(2, 1, 3, 'B'));
    ranges.emplace_back(std::make_tuple(1, 2, 7, 'C'));
    ranges.emplace_back(std::make_tuple(3, 4, 5, 'D'));
    ranges.emplace_back(std::make_tuple(0, 5, 7, 'E'));
    ranges.emplace_back(std::make_tuple(2, 6, 10, 'F'));
    ranges.emplace_back(std::make_tuple(1, 8, 9, 'G'));
    ranges.emplace_back(std::make_tuple(0, 9, 18, 'H'));
    ranges.emplace_back(std::make_tuple(2, 11, 13, 'I'));
    ranges.emplace_back(std::make_tuple(1, 12, 15, 'J'));
    ranges.emplace_back(std::make_tuple(2, 14, 15, 'K'));
    ranges.emplace_back(std::make_tuple(2, 16, 17, 'L'));

    auto view = eopi::trees::algorithms::view_from_above(ranges);
    cout << "[view from above]\n";
    for (auto v : view) {
      cout << "\t" << v.first << ": " << v.second << endl;
    }
  }
  {
    using eopi::trees::make_node;
    std::shared_ptr<eopi::trees::BinaryTreeNode<int>> null;
    auto tree = make_node(
        314, make_node(6, make_node(271, make_node(28), make_node(0)),
                       make_node(561, null, make_node(3, make_node(17)))),
        make_node(6, make_node(2, null, make_node(1, make_node(401, null,
                                                               make_node(641)),
                                                  make_node(257))),
                  make_node(271, null, make_node(28))));

    eopi::trees::print_levels_alternating(tree);
  }
}
