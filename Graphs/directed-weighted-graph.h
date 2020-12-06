#pragma once
#include<iostream>
#include<vector>
#include<map>
#include<set>


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
        std::vector<int> get_vertices_values(){
            std::vector<int> return_vector;

            for(auto map_element : _adjacency_map)
                return_vector.push_back(map_element.first._value);

            return return_vector;
        }

};
