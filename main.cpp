#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

#include <unordered_map>
#include "wordgraph.h"

std::string cleanString(std::string& str);
std::vector<std::string> getWords(std::string& str);

int main() {
  Wordgraph graphs;

  graphs.insert("Shakespeare_data.csv");
  // graphs.insert("test_data_hard.csv");
  graphs.print();
  
  std::vector<Wordgraph::Node*> gen = graphs.getShortestPath(graphs.getRandStartNode(), graphs.getRandEndNode());
  for(auto cur: gen){
    std::cout << cur->word << ' ';
  }
  std::cout<<'\n';
  
  auto cur =  graphs.getSCC(3,100);
  for(auto tmp: cur){
    for(auto c: tmp){
      cout << c <<" ";
    }
    cout <<'\n';
  }
  return 0;
}