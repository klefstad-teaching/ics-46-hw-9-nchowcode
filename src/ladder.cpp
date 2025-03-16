#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << "Error with words: " << word1 << " and " << word2 << msg << endl;
}

// Generates the word ladder from begin_word to end_word using the provided word_list
// Returns a vector of strings representing the ladder, or an empty vector if no ladder is found
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> letter_queue;
    set<string> visited;

    letter_queue.push({begin_word});
    visited.insert(begin_word);

    while (!letter_queue.empty()) {
        vector<string> ladder = letter_queue.front();
        letter_queue.pop();
        string last_word = ladder.back();

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
            
                if (word == end_word) {  
                    return new_ladder;
                }
                
                letter_queue.push(new_ladder);
            }
        }
    }
    error(begin_word, end_word, "No word ladder found.");
    return {};
}

// Call edit_distance_within to check if two words are adjacent with a distance of 1
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

// Use this to find the number of edits to get from str1 to str2
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int count = 0;
    int strlen1 = str1.length();
    int strlen2 = str2.length();

    // Early exit if lengths differ by more than d, impossible case.
    if (abs(strlen1 - strlen2) > d) {
        return false;
    }

    // Same length, check if they differ by d
    if (strlen1 == strlen2) {
        for (int i = 0; i < strlen1; ++i) {
            if (str1[i] != str2[i]) {
                count++;
            }
        }
        return count <= d;
    }

    const string& shorter_str = (strlen1 < strlen2) ? str1 : str2;
    const string& longer_str= (strlen1 < strlen2) ? str2 : str1;

    return is_within_one_edit(shorter_str, longer_str);
}

// Helper function to handle 1 char difference for edit_distance
bool is_within_one_edit(const string& shorter, const string& longer) {
    if (shorter.length() + 1 != longer.length()) {
        return false;
    }
    
    for (size_t i = 0; i <= shorter.length(); i++) {
        bool prefix_matches = true;
        bool suffix_matches = true;
        
        for (size_t j = 0; j < i; j++) {
            if (shorter[j] != longer[j]) {
                prefix_matches = false;
                break;
            }
        }
        
        if (!prefix_matches) continue;
        
        for (size_t j = i; j < shorter.length(); j++) {
            if (shorter[j] != longer[j+1]) {
                suffix_matches = false;
                break;
            }
        }
        
        if (prefix_matches && suffix_matches) {
            return true;
        }
    }
    
    return false;
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        error("File Error", file_name, "Could not open file.");
        return;
    }

    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    cout << "Word ladder found: ";
    for (const string& word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}