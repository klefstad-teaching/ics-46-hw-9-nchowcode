#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg); // done
bool edit_distance_within(const std::string& str1, const std::string& str2, int d); // done
bool is_adjacent(const string& word1, const string& word2); //done
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list);
void load_words(set<string> & word_list, const string& file_name);
void print_word_ladder(const vector<string>& ladder);
void verify_word_ladder();

// Helper Function
bool is_within_one_edit(const string& shorter, const string& longer);
