#pragma once 
#include <vector>
#include <algorithm>
using std::vector;
#include <string>
using std::string;
using std::pair;
#include <queue>
#include <map>
#include <unordered_map>
using std::map;
using std::pair;
#include <climits>
#include <queue>
#include <chrono>
#include <random>
#include <stack>
using namespace std;

class Wordgraph {
    public:
        struct Node{
            Node();
            Node(string s): word(s) {};

            string word;
            std::vector<std::pair<Node*, int>> adjacent;
        };

        Wordgraph();
        ~Wordgraph();

        void insert(std::string file);
        void insert(std::vector<std::string> sentence);
        

        std::vector<Node*> bfs(Node*& start);
        std::vector<Node*> dfs(Node*& start);
        std::vector<Node*> getShortestPath(Node* start, Node* end);
        std::vector<std::vector<std::string>>  getSCC(unsigned min, unsigned max);

        void print();
        Node* isInList(Node* head, string word);
        Wordgraph::Node* getRandNode();
        Wordgraph::Node* getRandStartNode();
        Wordgraph::Node* getRandEndNode(); 
        Wordgraph::Node* getNode(std::string str); 
        Node* root;  
    private:
        std::unordered_map<std::string, Node*> adj_list;
        
        Wordgraph getTranspose();
        void fillOrder(Node*& vertex, std::map<std::string, bool>& visited, std::stack<Node*> & stac);
        std::vector<std::string> SCCUtil(Node* vertex, std::map<std::string, bool>& visited); 
        int vectorSearch(string word);
        int addToAdjList(string word);
        void addToLinkedList(Node*& head, Node*& curr);
        void dfs_helper(Node* curr, vector<bool>& visited, vector<Node*>& toReturn);      
        double cost(std::pair<Node*, int> pair);
};