# Code Stack 

# Table of contents
- [Installation](#installation)
- [Graphs](#graphs)
    - [Summary](#summary)
    - [Features](#features)
    - [Depth First Search](#dfs)
        - [Applications](#applications)
    

# Installation
To use the .h files in C++, download the file and use
  ```C++
  #include "NAME OF FILE"
  ```
<br>In place of "template", "T" will be used in the remainder of document.

# Graphs

### Summary
A graph is a data structure containing a set of vertices and a set of edges.<br>
Adding value to vertices the graph becomes **undirected and unweighted**.<br>
A graph becomes **directed** when it's edges get directions, e.g. if an edge connects vertices A and B,<br>
it can be directed in a way that you can only traverse from A to B, not from B to A.
Each edge can also have a number(that can also be negative) representing it's weight, thus making the graph a **directed weighted graph**.

### Features
| Function            | Parameters' types    | Output            | Description                                                                                        |
|---------------------|:--------------------:|:-----------------:|----------------------------------------------------------------------------------------------------|
| add_vertex          | Vertex<T>            | -                 | Adding a vertex to the graph                                                                       |
| add_edge            | T,T                  | -                 | Adding an edge connecting vertices with given values                                               |
| add_edge            | Vertex<T>, Vertex<T> | -                 | Adding an edge connecting the given vertex objects                                                 |
| delete_vertex       | T                    | -                 | Deleting the vertex with the given value                                                           |
| delete_graph        | -                    | -                 | Deleting all graph elements                                                                        |
| show_graph          | -                    | -                 | Prints out all graph elements                                                                      |
| show_vertices       | -                    | -                 | Prints out all graph vertices                                                                      |
| show_edges          | -                    | -                 | Prints out all graph edges                                                                         |
| get_vertices        | -                    | vector<vertex<T>> | Returns a vector containing the vertex objects within the graph                                    |
| get_vertices_values | -                    | vector<T>         | Returns a vector containing the values of the vertices within the graph                            |
| edge_weight         | T,T                  | double            | Returns a double representing the weight of the edge connecting the vertices with the given values |
| DFS                 | T                    | map<T,bool>       | [DFS](#dfs)                                                                                        |
  
## DFS

Depth First Search is a traversing algorithm, meaning it can be use to visit vertices in a graph, possibly searching for a specific value or determining which vartices are disconnected from the graph.<br>
DFS takes a starting point as input and then follows a simple algorithm to visit as many nodes as possible.<br>
```C++
for each vertex V in graph G:
    mark V as unvisited
for each vertex U which is a neighbor of V:
    mark U as visited
    DFS(U)
```
The algorithm runs in `O(|E| + |V|)` time where |E| and |V| represent the number of edges and vertices in the graph, respectively.<br>

### Applications

DFS is an algorithm humans use when solving a maze, following a path until reaching a wall, then backtracking and doing the same until a path that leads to a solution is found.<br>
The same can be used in programming to both create a maze and to solve it.<br>

Another application would be finding out which parts of a graph are disconnected by checking which vertices haven't been visited by the algorithm.<br>

