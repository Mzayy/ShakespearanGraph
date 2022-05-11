#include "catch/catch.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <string>

#include <unordered_map>
#include <iostream>
#include "wordgraph.h"

using namespace std;
// using namespace Wordgraph;

TEST_CASE("testBFS simple", "[bfs simple]")
{
	Wordgraph graph;
    graph.insert("test_data_simple.csv");
    std::vector<Wordgraph::Node*> trav = graph.bfs(graph.root);

    std::vector<std::string> answer{"a", "b", "c", "d", "e", "f", "g", "h"};
    graph.insert(answer);
    for (int i = 0; i < (int)answer.size(); i++) {
        REQUIRE(answer[i] == trav[i]->word);
    }
}

TEST_CASE("testBFS hard", "[bfs hard]")
{
	Wordgraph graph;
    graph.insert("test_data_hard.csv");
    std::vector<Wordgraph::Node*> trav = graph.bfs(graph.root);

    std::vector<std::string> answer{"the", "wacky", "fireman", "bagel", "wazy", "crazy", "ate"};
    // std::cout<<"trav size = "<<trav.size()<<endl;
    for (int i = 0; i < (int)answer.size(); i++) {
        REQUIRE(answer[i] == trav[i]->word);
    }
}

TEST_CASE("testDFS simple", "[dfs simple]")
{
    Wordgraph graph;
    graph.insert("test_data_simple.csv");
    vector<Wordgraph::Node*> trav = graph.dfs(graph.root);

    vector<string> answer{"a", "b", "c", "d", "e", "f", "g", "h"};
    for (unsigned i = 0; i < answer.size(); i++) {
        REQUIRE(answer[i] == trav[i]->word);
    }
}
TEST_CASE("testDFS hard", "[dfs hard]") 
{
    Wordgraph graph;
    graph.insert("test_data_hard.csv");
    vector<Wordgraph::Node*> trav = graph.dfs(graph.root);

    vector<string> answer{"the", "fireman", "ate", "bagel", "wacky", "wazy", "crazy"};

    for(unsigned i = 0; i < answer.size(); i++) {
        REQUIRE(answer[i] == trav[i]->word);
    }
}

TEST_CASE("shortest path simple")
{   
    Wordgraph graph;
    graph.insert("test_data_simple.csv");
    Wordgraph::Node* start = graph.getNode("a");
    Wordgraph::Node* end = graph.getNode("b");
    vector<Wordgraph::Node*> path = graph.getShortestPath(start, end);
    vector<string> answer{"a","b"};
    for(unsigned i = 0; i < answer.size(); i++) {
        REQUIRE(answer[i] == path[i]->word);
    }
}

TEST_CASE("shortest path hard")
{
    Wordgraph graph;
    graph.insert("test_data_hard.csv");
    Wordgraph::Node* start = graph.getNode("fireman");
    Wordgraph::Node* end = graph.getNode("wazy");
    vector<Wordgraph::Node*> path = graph.getShortestPath(start, end);
    vector<string> answer{"fireman", "ate", "the", "wacky", "wazy"};
    for(unsigned i = 0; i < answer.size(); i++) {
        REQUIRE(answer[i] == path[i]->word);
    }
}

TEST_CASE("SSC Test simple")
{
    Wordgraph graph;
    graph.insert("test_data_simple.csv");
    std::vector<std::vector<std::string>> scc = graph.getSCC(0,2);
    vector<char> answer{'g','a','c','e','f','b','d','h'};
    for(unsigned i = 0; i < answer.size(); i++) {
        REQUIRE(scc[i][0].at(0) == answer[i]);
    }
}

TEST_CASE("SSC Test hard")
{
    Wordgraph graph;
    graph.insert("test_data_hard.csv");
    std::vector<std::vector<std::string>> scc = graph.getSCC(0,10);
    vector<string> answer{"the", "fireman", "ate", "bagel", "wacky", "wazy", "crazy"};
    for(unsigned i = 0; i < answer.size(); i++) {
        REQUIRE(scc[0][i] == answer[i]);
    }
}
//test disconnected