#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg) {
    cout << msg << word1 << word2 << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size();
    int len2 = str2.size();
    if (abs(len1 - len2) > d) {
        return false;
    }

    if (d == 1) {
        if (len1 == len2) {
            int mismatchCount = 0;
            for (int i = 0; i < len1; i++) {
                if (str1[i] != str2[i]) {
                    mismatchCount++;
                    if (mismatchCount > 1) return false;
                }
            }
            return (mismatchCount == 1);
        }
        else {
            const string& longer = (len1 > len2) ? str1 : str2;
            const string& shorter = (len1 > len2) ? str2 : str1;
            int i = 0, j = 0;
            int mismatchCount = 0;
            while (i < (int)longer.size() && j < (int)shorter.size()) {
                if (longer[i] != shorter[j]) {
                    mismatchCount++;
                    if (mismatchCount > 1) return false;
                    i++;
                } else {
                    i++;
                    j++;
                }
            }
            if (i < (int)longer.size()) {
                mismatchCount++;
            }
            return (mismatchCount == 1);
        }
    }
    return false;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return {};
    }
    queue<vector<string>> ladder_q;
    ladder_q.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_q.empty()) {
        vector<string> ladder = ladder_q.front();
        ladder_q.pop();

        string last_word = ladder.back();

        for (auto const &candidate : word_list) {
            if (is_adjacent(last_word, candidate)) {
                if (visited.find(candidate) == visited.end()) {
                    visited.insert(candidate);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(candidate);
                    if (candidate == end_word) {
                        return new_ladder; }
                    ladder_q.push(new_ladder);
                }
            }
        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream in(file_name);
    if (!in.is_open()) {
        cerr << "Failed to open file: " << file_name << endl;
        return;
    }
    string word;
    while (in >> word) {
        word_list.insert(word);
    }
    in.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}

void verify_word_ladder() {
    vector<string> testLadder = {"car", "cat", "chat", "cheat"};
    for (size_t i = 1; i < testLadder.size(); i++) {
        if (!is_adjacent(testLadder[i-1], testLadder[i])) {
            cout << "Invalid ladder: " << testLadder[i-1] << " -> " << testLadder[i] << " is not valid adjacency. " << endl;
            return;
        }
    }
    cout << "Ladder is valid!" << endl;
}
