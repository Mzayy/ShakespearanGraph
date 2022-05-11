#include "wordgraph.h"
#include <queue>
#include <stack>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>

using namespace std;

/**
 * @brief standardize lines
 * 
 * @param str The string to be cleaned of all non-alphanumeric characters
 * @return std::string with no punctuation in all lowercase
 */
std::string cleanString(std::string& str){
  for(unsigned i = 0; i < str.length(); i++){
    str.at(i) = std::tolower(str.at(i));
    if(!std::isalpha(str.at(i)) && str.at(i) != ' '){
      str.erase(i, 1);
      i--;
    } 
  }
  return str;
}

/**
 * @brief Get node for testing purposes
 * 
 * @param str The string to find
 * @return The node of that string
 */
Wordgraph::Node* Wordgraph::getNode(std::string str){
    return adj_list.find(str)->second;
}

/**
 * @brief Split sentence into words
 * 
 * @param str with spaces
 * @return vector with all separate words as elements
 */
std::vector<std::string> getWords(std::string& str){
  std::istringstream iss(str);
  std::vector<std::string> ret{std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
  return ret;
}

/**
 * @brief Basic Constructor for Wordgraph, makes one root node
 */
Wordgraph::Wordgraph(){
    // default constructor
    root = new Node("$");
    adj_list.insert(make_pair("$", root));
}

/**
 * @brief Basic destructor for wordgraph
 */
Wordgraph::~Wordgraph(){
    for(auto cur: adj_list){
        delete cur.second;
    }
}

/**
 * @brief Searches for the pseudo-index of the word in the map
 * 
 * @param word to search
 * @return pseudo-indexed location of word or -1 if not found
 */
int Wordgraph::vectorSearch(string word){
    //linear search thru adj_list to see if word is on graph
    //returns index or -1
    int counter = 0;
    for (auto cur : adj_list) {
        Node* node = cur.second;
        if (node->word == word) {
            return counter;
        }
        counter++;
    }
    return -1;
}

/**
 * @brief Gets random node, used primarily for sentence generation
 * 
 * @return Node that is at the start of at least one sentence
 */
Wordgraph::Node* Wordgraph::getRandStartNode(){
    std::random_device rng;
    std::mt19937 urng(rng());
    Node* temp = root;
    vector<Node*> startvec;
    for(auto cur: temp->adjacent){
        startvec.push_back(cur.first);
    }
    std::shuffle(startvec.begin(), startvec.end(), urng);
    if (startvec[0]->word == "$") {
        return startvec[0]->adjacent[0].first;
    }
    return startvec[0];
}

/**
 * @brief Gets random node, used primarily for sentence generation
 * 
 * @return Node that is never followed by another word
 */
Wordgraph::Node* Wordgraph::getRandEndNode(){
    std::random_device rng;
    std::mt19937 urng(rng());
    vector<Node*> endvec;
    for (auto pair : adj_list) {
        Node* head = pair.second;
        if (head->adjacent.size() == 0) {
            endvec.push_back(head);
        }
    }
    std::shuffle(endvec.begin(), endvec.end(), urng);
    return endvec[0];
}

/**
 * @brief Takes a filname and inserts its sentences into the graph
 * 
 * @param filename Name of the file in csv format
 */
void Wordgraph::insert(std::string filename){
    std::ifstream infile(filename);
    std::vector<std::string> lines;
    std::string line;

    while(std::getline(infile, line)){
        lines.push_back(cleanString(line));
    }

    std::vector<std::vector<std::string>> words;
    for(unsigned i = 0; i < lines.size(); i++){
        words.push_back(getWords(lines[i]));
    }

    for(std::vector<std::string> cur: words){
        insert(cur);        
    }
}

/**
 * @brief Insert helper function that takes in individual sentences and inserts them appropriately
 * 
 * @param sentence Sentence to insert into the graph
 */
void Wordgraph::insert(std::vector<std::string> sentence) {
    // insert a sentence onto graph
    Node* cur = root;
    Node* tmp;
    for (string word : sentence) {
        auto it = adj_list.find(word);
        if (it == adj_list.end()) {
            // word is not in adj_list
            Node* store = new Node(word);
            tmp = store;            
        }   
        else{
            tmp = it->second;
        }
        addToLinkedList(cur, tmp);
        //search for cur in tree
        if (adj_list.count(word) == 0) {
            // word is not in adj_list
            adj_list.insert(make_pair(word, tmp));
            tmp->adjacent = std::vector<std::pair<Node*, int>>();
            cur = tmp;
        } else {
            // word is in adj_list
            cur = adj_list.find(word)->second;
        }
    }
}

/**
 * @brief Adds a word to the adjacency list of its predecessor
 * 
 * @param head The previous node in the sentence
 * @param curr The current node
 */
void Wordgraph::addToLinkedList(Node*& head, Node*& curr){
    std::pair<Node*, int>* isin = nullptr;
    for(auto cur: head->adjacent)
        if(cur.first->word == curr->word)
            isin = &cur;
    if (!isin) {
        // word is not in linked list
        head->adjacent.push_back(make_pair(curr, 1));
    } else {
        // word is in linked list
        isin->second++;
    }
}

/**
 * @brief breadth first search
 * 
 * @param Node The node to start the traversal from
 * @return std::vector<Wordgraph::Node*> a vector of Nodes in order of the traversal
 */
std::vector<Wordgraph::Node*> Wordgraph::bfs(Node*& start) {
    std::vector<Node*> toReturn;
    int index = vectorSearch(start->word);
    std::vector<bool> visited;
    for (int i = 0; i < (int)adj_list.size(); i++) {
        visited.push_back(false);
    }
    std::queue<Node*> queue;
    visited[index] = true;
    queue.push(start);
    std::vector<Node*>::iterator i;
    Node* curr;
    while (!queue.empty()) {
        curr = queue.front();
        index = vectorSearch(curr->word);
        queue.pop();
        for (auto cura: adj_list.find(curr->word)->second->adjacent) {
            Node* cur = cura.first;
            int thisIndex = vectorSearch(cur->word);
            if (!visited[thisIndex]) {
                visited[thisIndex] = true;
                queue.push(cur); //(*i)?
                toReturn.push_back(cur);
            }
        }
    }
    return toReturn;
}

/**
 * @brief depth first search
 * 
 * @param start The node to start the traversal from
 * @return std::vector<Wordgraph::Node*> a vector of Nodes in order of the traversal
 */
std::vector<Wordgraph::Node*> Wordgraph::dfs(Node*& start) {
    //initialize vectors, and take care of the condition for the start index
    std::vector<Node*> toReturn;
    int index = vectorSearch(start->word);
    std::vector<bool> visited;
    for(unsigned i = 0; i < adj_list.size(); i++) {
        visited.push_back(false);
    }
    visited[index] = true;
    // keep track of the current node you are on
    Wordgraph::Node* curr = start;
    // go through visited vector and call dfs helper if it hasn't been visited yet
    for(unsigned i = 0; i < adj_list.size(); i++) {
        if (!visited[i]) {
            dfs_helper(curr, visited, toReturn);
        }
    }
    return toReturn;
}


/**
 * @brief depth first search recursive helper
 * 
 * @param curr The current node the traversal is at
 * @param visited the vector of which nodes have been visited
 * @param toReturn the vector of the order in which the nodes have been visited.
 * @return std::vector<Wordgraph::Node*> a vector of Nodes in order of the traversal
 */
void Wordgraph::dfs_helper(Wordgraph::Node* curr, vector<bool>& visited, vector<Wordgraph::Node*>& toReturn) {
    // create a stack and push the current node
    stack<Wordgraph::Node*> stack;
    stack.push(curr);
    // iterate through the stack
    while(!stack.empty()) {
        // get the top part of the stack and remove it
        curr = stack.top();
        stack.pop();
        // iterate through the stack's top's neighbors
        for (auto cura: adj_list.find(curr->word)->second->adjacent) {
            Node* cur = cura.first;
            int i_index = vectorSearch(cur->word);
            // if the current's neighbor hasn't been visited
            if(!visited[i_index]) {
                // mark as visited and push to stack and toReturn
                visited[i_index] = true;
                stack.push(cur);
                toReturn.push_back(cur);
                // call the recursive method on the current node, since it hasn't been visited.
                dfs_helper(cur, visited, toReturn);
            }
        }
    }
}

/**
 * @brief Prints all adjacency lists (Mosltly for testing)
 * 
 */
void Wordgraph::print() {
    for (auto node : adj_list) {
        std::cout<< node.first <<" -> ";
        for (auto cura: node.second->adjacent) {
            Node* cur = cura.first;
            std::cout<<cur->word<<" -> ";
        }
        std::cout<<std::endl;
    }
}

/**
 * @brief Uses Djikstra's algorithm to generate shortest path between start and end node
 * 
 * @param start The node to begin at
 * @param end The node to end at
 * @return Vector of nodes that are on the path from the shortest path from beginning to end
 */
vector<Wordgraph::Node*> Wordgraph::getShortestPath(Node* start, Node* end) {
    vector<Node*> ret;
    map<Node*, double> distance;
    map< Node*, Node*> previous;
    map<Node*, std::map<Node*, int>> visited;

    for (auto cur: adj_list) {
        auto word = cur.second;
        distance[word] = 9999;
        previous[cur.second] = NULL;
        visited[word] =  std::map<Node*, int>();
    }
    distance[start] = 0;

    priority_queue<pair<double,Node*>, vector<pair<double,Node*>>, greater<pair<double,Node*>>> prioq;
    for (auto it = distance.begin(); it != distance.end(); it++) {
        prioq.push(make_pair(it->second, it->first));
    }
    std::cout<<"The sentence starting from: \""<<prioq.top().second->word<< "\" and ending with: \"" << end->word << "\" is: " << std::endl;
    while (!prioq.empty()) {
        pair<double,Node*> cur = prioq.top();
        prioq.pop();
        double curDist = cur.first;
        Node* curNode = cur.second;
        for (auto cura: adj_list.find(curNode->word)->second->adjacent) {
            Node* temp = cura.first;
            if (cost(cura) + curDist < distance[temp] && visited[curNode].count(temp) == 0) {
                distance[temp] = cost(cura) + curDist;
                previous[temp] = curNode;    
                prioq.push(make_pair(cost(cura) + curDist, temp));   
                visited[curNode].insert(make_pair(temp, 1)); 
                
            }
        }
        
    }

    for (Node* temp = end; temp != nullptr && temp != start; temp = previous[temp]) {
        ret.push_back(temp);
    }
    ret.push_back(start);
    reverse(ret.begin(), ret.end());
    return ret;
}

/**
 * @brief Small helper that returns the cost of traveling an edge
 * 
 * @param pair The pair in the adjacency list of a node
 * @return cost, which is simply inverse of occurances
 */
double Wordgraph::cost(std::pair<Node*, int> pair){
    return 1/(double)pair.second;
}

/**
 * @brief SCC helper
 * 
 * @param vertex Node to begin on 
 * @param visited Map of whether or not each node was visited
 * @return std::vector<std::string> 
 */
std::vector<std::string> Wordgraph::SCCUtil(Node* vertex, std::map<std::string, bool>& visited){
    visited[vertex->word] = true;
    std::vector<std::string> ret({vertex->word});  

    for(auto it = vertex->adjacent.begin(); it != vertex->adjacent.end(); ++it)
        if(!visited[it->first->word]){
            std::vector<std::string> add = SCCUtil(it->first, visited);
            for(auto cur: add)
                ret.push_back(cur);
        }
    return ret;
}

/**
 * @brief Makes transpose of graph (all edges are reversed)
 * 
 * @return Transpose of our base graph
 */
Wordgraph Wordgraph::getTranspose(){
    Wordgraph g;
    for(auto cur = adj_list.begin(); cur != adj_list.end(); ++cur){
        g.adj_list.insert(make_pair(cur->first, new Node(cur->first)));
    }
    g.adj_list.erase("$");

    for(auto cur: g.adj_list){
        for(auto it = adj_list[cur.first]->adjacent.begin(); it != adj_list[cur.first]->adjacent.end(); ++it){
            if(it->first->word != "$" && cur.first != "$")
                g.adj_list[it->first->word]->adjacent.push_back(make_pair(cur.second, it->second));
        }
    }

    return g;
}

/**
 * @brief Adds all nodes adjacent to vertex in a stack with no duplicates
 * 
 * @param vertex The current node we wish to add to the stack with its neighbors
 * @param visited Map of whether or not each node was visited
 * @param stac The stack of nodes to go through in the end
 */
void Wordgraph::fillOrder(Node*& vertex, std::map<std::string, bool>& visited, std::stack<Node*> & stac){
    visited[vertex->word] = true;
    
    for(auto cura: vertex->adjacent){
        Node* tmp = cura.first;
        if(!visited[tmp->word]){
            fillOrder(tmp, visited, stac);
        }
    }
    stac.push(vertex);    
}

/**
 * @brief Prints all strongly connected components within a specified range
 * 
 * @param min Minimum nnumber of nodes in a scc to qualify it
 * @param max Maximum nnumber of nodes in a scc to qualify it
 */
std::vector<std::vector<std::string>> Wordgraph::getSCC(unsigned min, unsigned max){
    std::stack<Node*> stac;
    std::vector<std::vector<std::string>> ret;
    std::map<std::string, bool> visited;
    for(auto cur = adj_list.begin(); cur != adj_list.end(); ++cur){
        visited[cur->first] = false;
    }

    for(auto cur = adj_list.begin(); cur != adj_list.end(); ++cur){
        if(!visited[cur->first])
            fillOrder(cur->second, visited, stac);
    }

    Wordgraph graph = getTranspose();

    for(auto cur = adj_list.begin(); cur != adj_list.end(); ++cur){
        visited[cur->first] = false;
    }
    std::cout << "The Strongly Connected Components in this work are:\n";
    while (!stac.empty()){
        Node* vertex = stac.top();
        stac.pop();
        if(vertex->word == "$")
            continue;

        if(!visited[vertex->word]){
            std::vector<std::string> scc = graph.SCCUtil(vertex, visited);
            if(scc.size() > min && scc.size() < max){
                ret.push_back(scc);
            }            
        }
    }
    return ret;
}