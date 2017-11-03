#ifndef EOPI_HASH_TRIE_HPP_
#define EOPI_HASH_TRIE_HPP_

#include <memory>
#include <string>
#include <vector>

namespace eopi {
namespace hash {
class TrieNode {
public:
  TrieNode() : children(26, nullptr) {}

  // check for a child at char `c`
  std::shared_ptr<TrieNode> get(char c) { return children[c - 'a']; };

  // set a child at c
  void set(char c, std::shared_ptr<TrieNode> child) {
    children[c - 'a'] = child;
  }

private:
  std::vector<std::shared_ptr<TrieNode>> children;
};

class Trie {
public:
  Trie() { root = std::make_shared<TrieNode>(); }

  void add(std::string const &str) {
    auto node = root;
    for (auto c : str) {
      auto next = node->get(c);
      if (next == nullptr) {
        next = std::make_shared<TrieNode>();
        node->set(c, next);
      }
      // descend
      node = next;
    }
  }

  std::string shortest_unique_prefix(std::string const &str) {
    auto node = root;
    for (std::size_t i = 0; i < str.size(); ++i) {
      auto next = node->get(str[i]);
      if (!next) {
        return str.substr(0, i + 1);
      }
      node = next;
    }
    return "";
  }

private:
  std::shared_ptr<TrieNode> root;
};

} // namespace hash
} // namespace eopi

#endif // EOPI_HASH_TRIE_HPP_
