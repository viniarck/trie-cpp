#pragma once
#include <algorithm>
#include <deque>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class TrieNode {
  public:
    TrieNode(char val = '\0') : val(val){};
    ~TrieNode(){};
    char val;
    std::unordered_map<char, TrieNode *> children;
    bool end = false;
};

class Trie {
  public:
    Trie(){};
    ~Trie() {
        std::deque<TrieNode *> nodes{this->root.get()};
        std::vector<TrieNode *> to_delete{};
        while (!nodes.empty()) {
            auto node = nodes.front();
            nodes.pop_front();
            for (auto [c, n] : node->children) {
                nodes.push_back(n);
            }
        }
        while (!to_delete.empty()) {
            delete to_delete.back();
            to_delete.pop_back();
        }
    }

    std::unique_ptr<TrieNode> root = std::make_unique<TrieNode>();

    void insert(std::string_view value) {
        TrieNode *node = root.get();
        for (auto &v : value) {
            if (node->children.find(v) == node->children.end()) {
                node->children[v] = new TrieNode(v);
            }
            node = node->children[v];
        }
        node->end = true;
    }

    bool has_prefix(std::string_view prefix) {
        TrieNode *node = root.get();
        for (auto &v : prefix) {
            if (node->children.find(v) == node->children.end()) {
                return false;
            }
            node = node->children[v];
        }
        return true;
    }

    bool has_word(std::string_view word) {
        TrieNode *node = root.get();
        for (auto &v : word) {
            if (node->children.find(v) == node->children.end()) {
                return false;
            }
            node = node->children[v];
        }
        return node->end;
    }

    auto all_words() {
        std::vector<std::string> words;
        auto nodes = std::deque<std::pair<TrieNode *, std::string>>{
            std::make_pair(this->root.get(), "")};
        while (!nodes.empty()) {
            auto value = nodes.front();
            nodes.pop_front();
            if (value.first->end) {
                words.push_back(value.second);
            }
            for (auto [ch, n] : value.first->children) {
                nodes.push_back(std::make_pair(n, value.second + ch));
            }
        }
        std::sort(words.begin(), words.end());
        return words;
    }
};
