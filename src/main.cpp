/*
    main.cpp
    Copyright (c) 2024-2026, Amit Gefen

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

namespace {

// A trie of characters. A tree-like data structure used to store a dynamic set
// of strings where each node represents a single character. This is a versatile
// data structure suitable for efficient storage and retrieval of strings,
// particularly where prefix-based searching is required.

template <typename CharType>
class Trie final {
 public:
  // Insert a string into the trie.
  void Insert(const std::basic_string_view<CharType> string_view) {
    Node* node = &root_;

    for (const CharType character : string_view) {
      auto [iterator, inserted] = node->child_node.try_emplace(character);

      if (inserted) {
        iterator->second = std::make_unique<Node>();
      }

      node = iterator->second.get();
    }

    node->end_of_string = true;
  }

  // Find the common prefix among all inserted strings.
  auto CommonPrefix() const {
    std::basic_string<CharType> common_prefix{};
    const Node* node = &root_;

    while (node->child_node.size() == 1 && !node->end_of_string) {
      const auto& [character, child] = *node->child_node.begin();

      common_prefix += character;
      node = child.get();
    }

    return common_prefix;
  }

 private:
  // Structure representing a node in the trie.
  struct Node final {
    std::unordered_map<CharType, std::unique_ptr<Node>> child_node{};
    bool end_of_string{false};
  };

  Node root_{};
};

}  // namespace

int main() {
  try {
    Trie<wchar_t> trie_1{};
    Trie<wchar_t> trie_2{};

    // Test 1.
    trie_1.Insert(L"123456");
    trie_1.Insert(L"1234");
    std::wcout << L"common prefix: " << trie_1.CommonPrefix() << '\n';

    // Test 2.
    trie_2.Insert(L"xabX");
    trie_2.Insert(L"xabXYZ");
    trie_2.Insert(L"xabXP");
    trie_2.Insert(L"xabXT");
    std::wcout << L"common prefix: " << trie_2.CommonPrefix() << '\n';

    return EXIT_SUCCESS;
  } catch (const std::exception& e) {
    // fputs instead of std::println: the error path must not throw again.
    std::fputs(e.what(), stderr);
    std::fputs("\n", stderr);
    return EXIT_FAILURE;
  }
}
