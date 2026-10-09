# Trie

A small C++23 demo of a trie, a tree-like data structure for storing strings and finding their common prefix.

## What it shows

| Operation | Method | Description |
|---|---|---|
| Insert a string | `Insert` | Adds a string to the trie character by character |
| Find the common prefix | `CommonPrefix` | Returns the longest prefix shared by all inserted strings |
| Support character types | `Trie<CharType>` | Uses a template to support different character types, including `wchar_t` |

The demo inserts two sets of strings and prints their common prefixes.

## Expected output

```text
common prefix: 1234
common prefix: xabX
```

The first test inserts `123456` and `1234`, producing `1234` as the common prefix.

The second test inserts an empty string and several strings beginning with `xabX`. Since an empty string is also inserted, the common prefix is empty.

## Notes

- Each node stores its child nodes in a `std::unordered_map`, keyed by character.
- Child nodes are managed by `std::unique_ptr`, providing automatic memory management and clear ownership.
- The root node represents the empty prefix.
- The `end_of_string` flag distinguishes a complete inserted string from a prefix that continues into child nodes.
- `Insert` traverses the input string iteratively, creating nodes as needed.
- `CommonPrefix` follows the only child while the current node has exactly one child and does not mark the end of an inserted string.
- Both operations are implemented without recursion.
- Insertion takes expected O(m) time for a string of length m, assuming expected constant-time hash-map operations.
- Finding the common prefix takes O(p) expected time, where p is the length of the returned prefix.
- Space complexity is O(N), where N is the total number of characters stored across the trie, counting shared prefixes only once in the actual node structure.

## Requirements

A C++23-compatible compiler and standard library.

## Build and Run

- [Build on Windows](https://github.com/AmitGDev/cpp-ci-template#build-on-windows)
- [Build on Linux](https://github.com/AmitGDev/cpp-ci-template#build-on-linux)

## Code Style

- [C++](https://github.com/AmitGDev/cpp-coding-standard)
- [Python](https://github.com/AmitGDev/cpp-ci-template#python)
- [CMake](https://github.com/AmitGDev/cpp-ci-template#cmake)

## License

MIT License. Copyright © 2024-2026 Amit Gefen.

---

**Last Updated:** 2026-10-25  
**Maintainer:** AmitGDev