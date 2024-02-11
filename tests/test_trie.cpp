#include <gtest/gtest.h>
#include "trie.h"
#include <algorithm>

TEST(trie, has_word){
    auto trie = Trie{};
    trie.insert("hello");
    trie.insert("vini");
    EXPECT_EQ(trie.has_word("vini"), true);
    EXPECT_EQ(trie.has_word("vin"), false);
    EXPECT_EQ(trie.has_word("ini"), false);
}

TEST(trie, has_prefix){
    auto trie = Trie{};
    trie.insert("hello");
    trie.insert("vini");
    EXPECT_EQ(trie.has_prefix("vini"), true);
    EXPECT_EQ(trie.has_prefix("vin"), true);
}


TEST(trie, all_words){
    auto trie = Trie{};
    std::vector<std::string> words = {"hello", "hellow", "vini", "vinicius"};
    std::sort(words.begin(), words.end());
    for (auto &c : words) {
        trie.insert(c);
    }
    auto res = trie.all_words();
    EXPECT_EQ(res, words);
}
