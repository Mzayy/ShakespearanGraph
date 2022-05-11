1. Leading Question:

  a. Create a graph that depicts the relationship between words in Shakespearean works. Through natural language processing of every line in every Shakespearean work we should be able to identify elements of language such as synonyms, frequent word pairs, separate word frequencies, Paradigmatic words (words that can be substituted for each other such as “Tuesday” and “Wednesday”), and Syntagmatic words (words that can be combined like “hot” and “weather”). The purpose of this is to visually depict elements of Shakespearean language in a way that illustrates the relationship between different words. We believe that this can provide a valuable insight into Shakepseare’s ‘unique’ usage of the English language, which is valuable because it confuses most modern English speakers, even though it’s the same language.
  
  b. The algorithms will answer this question by determining clusters of popular and frequently used Shakespearean words through our strongly connected component algorithm. By determining these words, we can identify the major tools(words) in Shakespeare's writing arsenal and potentially their context and meaning. Additionally, our shortest path algorithm will be able to generate new sentences in Shakespeare's dialect even though he has been dead for centuries. This may provide valuable insight into sentence generation and Shakespeare's writing process.
  
  c. For more information on Natural Language processing: https://www.youtube.com/watch?v=BVMx24dtko0&ab_channel=Neo4j
  
2. Dataset Acquisition:

  a. Our dataset will be every line of every Shakespeare play. We got our dataset from kaggle: https://www.kaggle.com/datasets/kingburrito666/shakespeare-plays, we will download the dataset as a CSV file. The dataset is 10.19 MB or 111,396 lines long. We plan to use the “PlayerLine” column of the dataset as it contains the lines from the play.
 
 b. We will check for missing entries by checking for null or length 0. If there is invalid or missing entries we will remove them from the dataset. There are also going to be a lot of apostrophes and commas in a line that we will have to remove, and Shakespeare frequently used apostrophes to replace letters in order to change the syllable count of a line. However, we need to keep any punctuation that occurs in the middle of a word like hyphens and apostrophes. Since our dataset contains the entire population of Shakespeare’s work, all values are physically possible. Some statistical outliers would be words that get used a very small number of times.
 
 c. We will use a text graph for our project. Text graphs are useful for text condensation, text summarization. It is good for breaking apart a large text chunk and analyzing it at a more specific level. The worst case runtime of a text graph assumes that there is not a single repeated word, in that case the runtime is O(n).

3. Graph Algorithms:

  a. Parse data and fill graph
  
    i. Purpose: prepare for graph algorithms
    
    ii. Input and Output: Takes csv from https://www.kaggle.com/datasets/kingburrito666/shakespeare-plays, outputs a graph of words. 
We store the graph as an Adjacency List, with a placeholder word as the root node of the graph. Edge Example Graph:
![alt text](https://cdn.discordapp.com/attachments/951670647493386291/958471809609654402/unknown.png)
    
    iii. Runtime Efficiency: 
    
      1. Parsing data: O(n)
      
      2. Adding a node: O(n) search and O(1) add 

  
  b. Depth First Search Traversal
  
    i. Purpose: Depth first search will be used in our strongly connected components algorithm. Additionally, it will be used for our Dijkstra’s algorithm when generating a shortest path graph.
    
    ii. Input and Output: Input root node of the graph. Output a full traversal of the graph.
    
    iii. Runtime Efficiency: O(V+E)

  
  c. Shortest Paths Algorithm (Dijkstra’s Algorithm)
  
    i. Purpose: To generate the shortest sentence possible using any two words in the graph. For example, we can input two strange words and determine how Shakespeare would write a sentence that begins with one word and ends with the other.
    
    ii. Input and Output: Input two Shakespearean words. Output a sentence that begins with the start word and ends with the end word(possibly original, possibly redone)
    
    iii. Runtime Efficiency: O(V2) 
    
  d. Strongly connected components (Kosaraju’s Algorithm)
  
    i. Purpose: To determine clusters of words that Shakespeare uses frequently in similar contexts
    
    ii. Input and Output: Input root. Output nodes in graphs that are strongly connected.
    
    iii. Runtime Efficiency: O(V+E)


4. Timeline (finish by):

  a. We will first need to parse the data, which will probably be done quickly and easily. 
  
    i. Read Data: 04/03

  b. The next thing to do would be to create a graph for this data and create algorithms such as traversals. 
  
    i. Create a graph: 04/05
    
    ii. BFS DFS: 04/12
    
    iii. Shortest Path: 04/19
    
    iv. Strongly Connected Components: 04/26

  c. Complete Potential Features

5. Potential Features

  a. Develop functions to assess how much a given resembles Shakespeare plays
  
  b. Generate summary of a given play using keywords.
 
 c. Given a word, find a synonym of that word based on context clues.
 
 d. Pagerank

