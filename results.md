# CS 225 Final Project Written Report
## Team: imsmurfing

### Goals:
The goal of our project was to take data that includes all of Shakespear’s plays and use natural language processing of every line in every Shakespearean work we should be able to identify elements of language such as synonyms, frequent word pairs, separate word frequencies, Paradigmatic words (words that can be substituted for each other such as “Tuesday” and “Wednesday”), and Syntagmatic words (words that can be combined like “hot” and “weather”). The purpose of this is to visually depict elements of Shakespearean language in a way that illustrates the relationship between different words. We believe that this can provide a valuable insight into Shakepseare’s ‘unique’ usage of the English language, which is valuable because it confuses most modern English speakers, even though it’s the same language.

### Algorithms:
1. Parse data and fill graph
  - We took the data of all of Shakespear’s plays in a csv file and makes split it by spaces and punctuation into a vector. We used this vector of words to insert it into an adjacency list. We also made a print() function to print out the graph. It works by printing out each word on a new line followed by what words that word is pointing to. An example of part of the graph is:
  - ![Wordgraph](https://keep.google.com/u/0/media/v2/15IMYpScajc6iB0pU5wlQjWJkMdFXgzPzoOoyH87CWqzLIXNX8JZHXBMJTEog-PA/1Leh3fMUbZiRh05ccYl4fPdyUT9uPi4mQRxm-H1qHWooyc380NlG3L-wkze3mlA?accept=image%2Fgif%2Cimage%2Fjpeg%2Cimage%2Fjpg%2Cimage%2Fpng%2Cimage%2Fwebp%2Caudio%2Faac&sz=1600)
2. Depth first search traversal
  - The depth first search traversal takes in the start node and uses the vectorSearch function to find the index of each node. We also used a boolean vector initialized to all false values to keep track of if a node at each index was visited already. For each unvisited node, we called on a helper function that used a stack to keep track of the nodes, adding unvisited nodes to the stack and also to the vector of nodes to return (order of the traversal). We called on the dfs helper again for each unvisited node, making this a recursive function.
  - Test case for the data: “A, B, C, D, E, F, G, H”. DFS returns: {“a”, “b”, “c”, “d”, “e”, “f”, “g”, “h”}.
  - Test case for the data: “The fireman are the balel, the wacky wazy, the wacky crazy, wacky bagel, wacky bagel, the wacky wazy, the wacky crazy, wacky bagel, wacky bagel”. DFS returns: {"the", "fireman", "ate", "bagel", "wacky", "wazy", "crazy"}.
3. Breadth first search traversal
  - The breadth first search traversal takes in the start node and also uses the vectorSearch function to find the index of each node. We also used a boolean vector initialized to all false values to keep track of if a node at each index was visited already. Using a queue, we added each node the queue as it was visited at each node popped from the queue, we visited it’s neighbors and if they were not visited already, we could add them to the queue and the vector to return and mark them as visited at their index in the visited vector. We did this until the queue was empty.
  - Test case for the data: “A, B, C, D, E, F, G, H”. BFS returns: {“a”, “b”, “c”, “d”, “e”, “f”, “g”, “h”}.
  - Test case for the data: “The fireman are the balel, the wacky wazy, the wacky crazy, wacky bagel, wacky bagel, the wacky wazy, the wacky crazy, wacky bagel, wacky bagel”. BFS returns: {"the", "wacky", "fireman", "bagel", "wazy", "crazy", "ate"}.
4. Shortest paths (Dijkstra’s Algorithm)
  - Using Dijkstra’s Algorithm, we are able to identify a shortest path connecting two given words on the graph. With an input start word and end word, the algorithm lets us generate sentences from the graph, with words that Shakespeare used consecutively. 
  - We also implemented random word selectors to generate random start and end words, which is used in the shortest path function.
  - This algorithm is a good foundation for auto play writers or text generators. With extra steps to select start and end words it will be a functioning play writer. Combined with other algorithms we can customize the sentence generated.
  - An example output for this function is: “The sentence starting from: “heapd” and ending with: “audaciously” is: heapd fond it is not to speak audaciously”
5. Strongly connected components (Kosaraju’s Algorithm)
  - Due to the vastness of Shakespeare’s work, we ended up getting a vast majority of the words used balled up into one singular strongly connected component. This is because in all of the works, the same words must’ve been used in enough context to make a very large connected component. As a result, the strongly connected component didn’t perform quite as expected. However, it did end up grouping up similar words together.
  - This algorithm used Kosaraju’s Algorithm which utilized a DFS and a transpose of the base graph to generate all strongly connected components.
  - An example of similar word grouping is: “servantone varros sevantist servanti servanttwas servanthang servanthow servantwhat servantthou servantsant”
  - Something cool about this is that the stand out word ‘varros’ is actually a character who owns servants and addresses them throughout the plays.
  - Overall, the strongly connected components didn’t act as expected, and to improve the results we’d likely have to narrow the graph to include a smaller part of Shakespeare’s works. However, we did discover that this algorithm can help find similes, as in the case: “uneducated unpruned untrained”.

### Conclusion
Overall, the project was a success and answered our leading question. We were able to correctly insert all of the Shakespeare plays into a graph and using the shortest path algorithm, make the shortest sentence possible that makes sense from one word to the next. The strongly connected components algorithm correctly identifies words that are closely related to each other in a Shakspearian context. Examples of this can be seen above. Additionally, BFS and DFS traverse the graph correctly and produced the correct spanning trees, but different ones because they are different traversals. Overall, we were able to accurately implement each algorithm we wanted to but we didn’t get a chance to implement any of the extra possible features we discussed in our proposal. 
