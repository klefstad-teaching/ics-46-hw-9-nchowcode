#include <gtest/gtest.h>
#include "dijkstras.h"
#include "ladder.h"

TEST(TestLadder, VerifyWordLadders) {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    
    // Test cat to dog (4 words total)
    vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    print_word_ladder(ladder);
    EXPECT_EQ(ladder.size(), 4);
    
    // Test marty to curls (6 words total)
    ladder = generate_word_ladder("marty", "curls", word_list);
    EXPECT_EQ(ladder.size(), 6);
    
    // Test code to data (6 words total)
    ladder = generate_word_ladder("code", "data", word_list);
    EXPECT_EQ(ladder.size(), 6);
    
    // Test work to play (6 words total)
    ladder = generate_word_ladder("work", "play", word_list);
    EXPECT_EQ(ladder.size(), 6);
    
    // Test sleep to awake (8 words total)
    ladder = generate_word_ladder("sleep", "awake", word_list);
    EXPECT_EQ(ladder.size(), 8);
    
    // Test car to cheat (4 words total)
    ladder = generate_word_ladder("car", "cheat", word_list);
    EXPECT_EQ(ladder.size(), 4);
}

TEST(TestLadder, TestIsAdjacent) {
    EXPECT_TRUE(is_adjacent("cat", "bat"));
    EXPECT_TRUE(is_adjacent("cat", "cot"));
    EXPECT_FALSE(is_adjacent("cat", "dog"));
    EXPECT_TRUE(is_adjacent("cat", "cats"));
}

TEST(TestDijkstra, TestShortestPath) {
    Graph G;
    file_to_graph("src/small.txt", G);
    
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(distances[1], 3);
    EXPECT_EQ(distances[2], 6);
    EXPECT_EQ(distances[3], 1);

  vector<int> path = extract_shortest_path(distances, previous, 3);

  print_path(previous, 3);
  EXPECT_EQ(path.size(), 2);  // Should be [0, 3] for a direct path
}