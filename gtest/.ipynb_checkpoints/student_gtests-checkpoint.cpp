#include <gtest/gtest.h>
#include "dijkstras.h"
#include "ladder.h"
#include <set>
#include <vector>
#include <string>

// Helper function to create test word lists
std::set<string> createWordList(const std::vector<std::string>& words) {
    return std::set<string>(words.begin(), words.end());
}

// Test the edit_distance_within function
TEST(EditDistanceTest, WithinDistanceOne) {
    EXPECT_TRUE(edit_distance_within("cat", "hat", 1));
    EXPECT_TRUE(edit_distance_within("dog", "fog", 1));
    EXPECT_TRUE(edit_distance_within("hello", "hallo", 1));
    EXPECT_FALSE(edit_distance_within("cat", "dog", 1));
    EXPECT_FALSE(edit_distance_within("hello", "world", 1));
}

TEST(EditDistanceTest, WithinDistanceTwo) {
    EXPECT_TRUE(edit_distance_within("hello", "hillo", 2));
    EXPECT_FALSE(edit_distance_within("hello", "world", 2));
    EXPECT_FALSE(edit_distance_within("computer", "keyboard", 2));
}

TEST(EditDistanceTest, EqualWords) {
    EXPECT_TRUE(edit_distance_within("cat", "cat", 0));
    EXPECT_TRUE(edit_distance_within("hello", "hello", 0));
}

TEST(EditDistanceTest, DifferentLengths) {
    EXPECT_TRUE(edit_distance_within("cat", "cats", 1));
    EXPECT_FALSE(edit_distance_within("cat", "catsup", 1));
    EXPECT_TRUE(edit_distance_within("hello", "hell", 1));
}

// Test the is_adjacent function
TEST(IsAdjacentTest, AdjacentWords) {
    EXPECT_TRUE(is_adjacent("cat", "hat"));
    EXPECT_TRUE(is_adjacent("dog", "fog"));
    EXPECT_TRUE(is_adjacent("hello", "hallo"));
}

TEST(IsAdjacentTest, NonAdjacentWords) {
    EXPECT_FALSE(is_adjacent("cat", "dog"));
    EXPECT_FALSE(is_adjacent("hello", "world"));
    EXPECT_FALSE(is_adjacent("computer", "keyboard"));
}

TEST(IsAdjacentTest, SameWords) {
    EXPECT_FALSE(is_adjacent("cat", "cat"));
    EXPECT_FALSE(is_adjacent("hello", "hello"));
}

// Test the generate_word_ladder function
TEST(WordLadderTest, SameBeginAndEndWord) {
    std::set<string> word_list = createWordList({"cat", "hat", "bat", "rat"});
    std::vector<string> ladder = generate_word_ladder("cat", "cat", word_list);
    EXPECT_TRUE(ladder.empty());
}

TEST(WordLadderTest, OneStepLadder) {
    std::set<string> word_list = createWordList({"cat", "hat", "bat", "rat"});
    std::vector<string> ladder = generate_word_ladder("cat", "hat", word_list);
    
    std::vector<string> expected = {"cat", "hat"};
    EXPECT_EQ(ladder, expected);
}

TEST(WordLadderTest, MultiStepLadder) {
    std::set<string> word_list = createWordList({"cat", "hat", "hot", "dot", "dog"});
    std::vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    
    // There could be multiple valid paths, so we'll just check the first and last elements
    // and ensure the length makes sense (cat->hat->hot->dot->dog = 5 steps)
    ASSERT_EQ(ladder.size(), 5);
    EXPECT_EQ(ladder.front(), "cat");
    EXPECT_EQ(ladder.back(), "dog");
    
    // Check that each step is a valid transition (edit distance of 1)
    for (size_t i = 0; i < ladder.size() - 1; ++i) {
        EXPECT_TRUE(is_adjacent(ladder[i], ladder[i+1]));
    }
}

TEST(WordLadderTest, ImpossibleLadder) {
    std::set<string> word_list = createWordList({"cat", "hat", "rat", "xyz", "abc"});
    std::vector<string> ladder = generate_word_ladder("cat", "xyz", word_list);
    EXPECT_TRUE(ladder.empty());
}

TEST(WordLadderTest, EmptyWordList) {
    std::set<string> word_list;
    std::vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    EXPECT_TRUE(ladder.empty());
}

// Test the load_words function
TEST(LoadWordsTest, ValidFile) {
    std::set<string> word_list;
    
    // Create a temporary file for testing
    std::ofstream temp_file("test_words.txt");
    temp_file << "cat\nhat\nbat\nrat\n";
    temp_file.close();
    
    load_words(word_list, "test_words.txt");
    
    EXPECT_EQ(word_list.size(), 4);
    EXPECT_TRUE(word_list.find("cat") != word_list.end());
    EXPECT_TRUE(word_list.find("hat") != word_list.end());
    EXPECT_TRUE(word_list.find("bat") != word_list.end());
    EXPECT_TRUE(word_list.find("rat") != word_list.end());
    
    // Clean up
    std::remove("test_words.txt");
}

TEST(LoadWordsTest, InvalidFile) {
    std::set<string> word_list;
    
    // Testing with a non-existent file
    // We expect the function to handle this gracefully (not crash)
    // The exact behavior depends on your implementation
    load_words(word_list, "nonexistent_file.txt");
    
    // The word list should either be empty or unchanged
    EXPECT_TRUE(word_list.empty());
}

// Add any additional tests needed for your specific implementation