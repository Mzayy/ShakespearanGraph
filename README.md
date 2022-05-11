# CS 225 Final Project: Shakespearean Words
## Team: imsmurfing
## Team members: Jake Hunnius, Sofia Perry, Mohammad Zayyad, David Zhu

All of our functions are in the `wordgraph.h/wordgraph.cpp` files. The `main.cpp` file has what the function outputs. The tests are in `tests.cpp`. The Shakespeare data that we are using (his plays), are in `Shakespeare_data.csv`. `test_hard.csv` and `test_simple.csv` are used for testing purposes. The written report is located in `results.md` and the video presentation is located in `presentation.md`. 

### Data
The data we are using includes all of Shakespeare’s works. The dataset we used can be found here: https://www.kaggle.com/datasets/kingburrito666/shakespeare-plays . 

### Exacutable/Running Instructions
##### The required inputs for each of the main algorithm functions are as follows:
1. `std::string cleanString(std::string& str)`
  - Input: a string (a line from the csv file)
  - Output: a cleaned string in all lowercase without white space, punctionuate, and unwanted characters. 
2. `std::vector<Wordgraph::Node*> Wordgraph::bfs(Node*& start)` (Breadth First Search)
  - Input: the node to start the traversal from
  - Output: a vector of nodes in the order they were visited/the order of the traversal
3. `std::vector<Wordgraph::Node*> Wordgraph::dfs(Node*& start)` (Depth First Search)
  - Input: the node to start the traversal from
  - Output: a vector of nodes in the order they were visited/the order of the traversal
4. `std::vector<Wordgraph::Node*> Wordgraph::getShortestPath(Node* start, Node* end)` (Dijkstra’s algorithm)
  - Input: the node to start at and the node to end at
  - Output: A vector of nodes that are on the path from the shortest path from the start node to the end node
5. `std::vector<std::vector<std::string>> Wordgraph::getSCC(unsigned min, unsigned max)` (Kosaraju’s algorithm)
  - Input: the minimum and maximum number of nodes in a strongly connected component to qualify it
  - Output: a vector of vectors of strings that include all the strongly connected components within a specified range. 


The code can be cloned into VSCode by putting `git clone https://github-dev.cs.illinois.edu/cs225-sp22/yuerzhu2-mzayy2-hunnius2-sofiaip2` into the terminal.

#### Running the code:
1. Type `make` into the terminal
2. Type `./main` into the terminal
#### Running test cases:
1. Type `make test` into the terminal
2. Type `./test` into the terminal
#### The test cases we have are:
1. testBFS simple and hard
  - Makes sure that the breadth first search function traverses through the graph in the correct order.
2. testDFS simple and hard
  - Makes sure that the depth first search function traverses through the graph in the correct order. 
3. Shortest path test simple and hard
  - Makes sure the generated paths are correct
4. Strongly Connected Components simple and hard
  - Makes sure that the words returned are related. 

