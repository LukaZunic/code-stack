#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<map>
#include<set>

#define INF 10000

/**
 * @brief A standard container for the template value of a vertex
 * @param _value Numeric value held by the vertex
 **/
template<typename T>
struct vertex{
    T _value;
    vertex(T value) : _value{value}{}

    // Overloading the < operator for the ability to use vertex as a key in a map
    bool operator<(const vertex &v) const{
        return _value < v._value || (_value == v._value && _value < v._value);
    }
};


template<typename T>
class DWGraph{
    public:

        /**
         * An implementation of neighboring relationships between vertices using a map.
         * The adjacency map is constructed in form:
         * (key, value) = (vertex, a set of pairs of neighboring vertices and the weight of the connecting edge)
         **/
        std::map<vertex<T>, std::set<std::pair<vertex<T>, double>>> _adjacency_map = {};

        // Default constructor
        DWGraph(){}
        


        /* ALTERING GRAPH */

        /**
         * @brief Add a new (and unique) vertex with no neighbors to the graph
         **/
        void add_vertex(T value){
            _adjacency_map[vertex<T>(value)] = {};
        }

        /**
         * @brief Overloaded addEdge function, if a vertex is not in the graph, it will be added automatically
         * 
         * @param v1 Vertex value (start of edge)
         * @param v2 Vertex value (end of edge)
         **/
        void add_edge(T v1, T v2, double weight){
            if(!(_adjacency_map.count(vertex<T>(v2)))) add_vertex(v2);
            _adjacency_map[vertex<T>(v1)].insert(std::pair<vertex<T>, double>(vertex<T>(v2), weight));
        }

        /**
         * @brief Overloaded addEdge function, if a vertex is not in the graph, it will be added automatically
         * 
         * @param v1 Vertex object (start of edge)
         * @param v2 Vertex object (end of edge)
         **/
        void add_edge(vertex<T> v1, vertex<T> v2, double weight){
            _adjacency_map[v1].insert(std::pair<vertex<T>, double>(v2, weight));
        }

        void delete_vertex(T v){
            if(!(_adjacency_map.count(vertex<T>(v)))){
                throw "Vertex is not in graph";
            }else{

                // removing vertex from graph
                _adjacency_map.erase(vertex<T>(v));
                
                // removing all edges containing deleted vertex
                for(auto map_element : _adjacency_map){
                    auto it = map_element.second.begin();
                    while (it != map_element.second.end()){
                        if ((*it).first._value == v){
                            it = map_element.second.erase(it);
                        }else{
                            ++it;
                        }
                    }
                }
            }
        }

        void delete_graph(){
            _adjacency_map = {};
        }

        /**************************************/

    
        /* SHOWING GRAPH COMPONENTS */

        void show_graph(){
            for(auto map_element : _adjacency_map){
                std::cout << map_element.first._value << " : ";

                for(auto set_element : map_element.second)
                    std::cout << "(" << set_element.first._value << ", weight=" << set_element.second << ") "; 

                std::cout << "\n";
            }
        }

        void show_vertices(){
            for(auto map_element : _adjacency_map) std::cout << map_element.first._value << std::endl;
        }

        void show_edges(){
            for(auto map_element : _adjacency_map){
                for(auto set_element : map_element.second)
                    if(!(map_element.second.empty()))
                        std::cout << "(" <<  map_element.first._value << "," << set_element.first._value << ", weight=" << set_element.second << ")" << std::endl; 
            }
        }
        /**************************************/




        /* RETURNING GRAPH COMPONENT VALUES */

        /**
         * @brief Function to fetch the INSTANCES of objects representing the vertices in a graph
         * @return A vector<vertex<T>> representing the collection of vertex objects
         **/
        std::vector<vertex<T>> get_vertices(){
            std::vector<vertex<T>> return_vector;

            for(auto map_element : _adjacency_map)
                return_vector.push_back(map_element.first);

            return return_vector;
        }

        /**
         * @brief Function to fetch the VALUES of objects representing the vertices in a graph
         * @return A vector<T> representing the collection of vertex values
         **/
        std::vector<T> get_vertices_values(){
            std::vector<T> return_vector;

            for(auto map_element : _adjacency_map)
                return_vector.push_back(map_element.first._value);

            return return_vector;
        }

        /**
         * @brief Function to fetch the value of the edge weight between two vertices
         * 
         * @param v1 Vertex object (start of edge)
         * @param v2 Vertex object (end of edge)
         * 
         * @return A double, the value of the (v1, v2) edge
         **/
        double edge_weight(T v1, T v2){
            for(auto map_element : _adjacency_map){
                if(map_element.first._value == v1)
                    for(auto set_element : map_element.second)
                        if(set_element.first._value == v2)
                            return set_element.second; 
            }
            throw "Edge does not have weight";
        }
        /**************************************/


        /** GRAPH ALGORITHMS **/

        /**
         * @brief Depth First Search is a traversing algorithm designed to visit all vertices connected with an arbitrarily given starting vertex.
         * Commencing from the given vertex, the algorithm traverses the graph in a way where it goes as far as possible following on a path,
         * then backtracking and traversing other possible paths
         * 
         * @param starting_vertex Starting vertex from which the algorithm commences
         * @return map<T, bool>, map in form {vertex from graph, bool representing if the vertex had been visited during DFS}
         **/
        std::map<T, bool> DFS(T starting_vertex){

            std::stack<T> S;
            std::map<T, bool> visited;
            S.push(starting_vertex);
            
            T temp;
            while(!S.empty()){
                temp = S.top();
                S.pop();
                if(!visited[temp]){
                    visited[temp] = true;
                    for(auto i : this->_adjacency_map[temp]){
                        S.push(i.first._value);
                    }
                }
            }

            return visited;
        }


        /**
         * @brief Breadth First Search is a traversing algorithm designed to visit all vertices connected with an arbitrarily given starting vertex.
         * Commencing from the given vertex, the algorithm traverses the graph in a way where it visits all the neighboring vertices of the current node,
         * then repeating the same for each visited node whose neighbors haven't all been visited yet.
         * 
         * @param starting_vertex Starting vertex from which the algorithm commences
         * @return map<T, bool>, map in form {vertex from graph, bool representing if the vertex had been visited during BFS}
         **/
        std::map<T, bool> BFS(T starting_vertex){

            std::queue<T> Q;
            std::map<T, bool> visited;
            Q.push(starting_vertex);

            for(auto map_element : this->_adjacency_map){
                visited[map_element.first._value] = false;
            }
            visited[starting_vertex] = true;

            T temp;
            while(!Q.empty()){
                temp = Q.front();
                Q.pop();
                
                for(auto i : this->_adjacency_map[temp]){
                    if(!visited[i.first._value]){
                        Q.push(i.first._value);
                        visited[i.first._value] = true;
                    }
                }
            }   

            return visited;
        }


        struct DijkstraOUTPUT{
            int shortestDistance;
            std::map<T,T> predecessorTree;
        };

        DijkstraOUTPUT Dijkstra(T start, T finish){

            std::map<T, int> D;
            std::map<T,T> predecessorTree;

            for(auto map_element : _adjacency_map){
                D[map_element.first._value] = INF;
                predecessorTree[map_element.first._value] = -1;
            }
            D[start] = 0;

            std::vector<T> S;
            std::priority_queue<T> Q;

            for(auto map_element : _adjacency_map){
                Q.push(-1 * map_element.first._value);
            }

            while(!Q.empty()){

                T u = -1 * Q.top();
                Q.pop();
                S.push_back(u);

                for(auto set_element : _adjacency_map[vertex<T>(u)]){
                    if(D[set_element.first._value] > D[u] + edge_weight(u, set_element.first._value)){
                        D[set_element.first._value] = D[u] + edge_weight(u,set_element.first._value);
                        predecessorTree[set_element.first._value] = u;
                    }
                }

            }

            return {D[finish], predecessorTree};
        }
       


};
