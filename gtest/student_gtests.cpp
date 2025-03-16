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
  
  // Test distance calculations
  EXPECT_EQ(distances[0], 0);
  EXPECT_EQ(distances[1], 3);
  EXPECT_EQ(distances[2], 6);
  EXPECT_EQ(distances[3], 1);
  
  // Test paths using extract_shortest_path
  vector<int> path0 = extract_shortest_path(distances, previous, 0);
  vector<int> path1 = extract_shortest_path(distances, previous, 1);
  vector<int> path2 = extract_shortest_path(distances, previous, 2);
  vector<int> path3 = extract_shortest_path(distances, previous, 3);
  
  // Check path from 0 to 0 (just source)
  EXPECT_EQ(path0.size(), 1);
  EXPECT_EQ(path0[0], 0);
  
  // Check path from 0 to 1
// Check path from 0 to 1
EXPECT_EQ(path1.size(), 3); 
EXPECT_EQ(path1[0], 0);
EXPECT_EQ(path1[1], 3);  // Going through vertex 3
EXPECT_EQ(path1[2], 1);

// Check path from 0 to 2
EXPECT_EQ(path2.size(), 4); 
EXPECT_EQ(path2[0], 0);
EXPECT_EQ(path2[1], 3);  // Going through vertex 3
EXPECT_EQ(path2[2], 1);  // Then vertex 1
EXPECT_EQ(path2[3], 2);
  
  // Check path from 0 to 3
  EXPECT_EQ(path3.size(), 2);
  EXPECT_EQ(path3[0], 0);
  EXPECT_EQ(path3[1], 3);
}