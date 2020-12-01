#pragma once
#include<iostream>
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
        void addVertex(T value){
            _adjacency_map[vertex<T>(value)] = {};
        }

        void showVertices(){
            for(auto mapElement : _adjacency_map) std::cout << mapElement.first._value;
        }

        void addEdge(T v1, T v2, double weight){
            _adjacency_map[vertex<T>(v1)].insert(std::pair<vertex<T>, double>(vertex<T>(v2), weight));
        }

        /**
         * @brief Overloaded addEdge function, if a vertex is not in the graph, it will be added automatically
         * 
         * @param v1 Vertex object (start of edge)
         * @param v2 Vertex object (end of edge)
         **/
        void addEdge(vertex<T> v1, vertex<T> v2, double weight){
            _adjacency_map[v1].insert(std::pair<vertex<T>, double>(v2, weight));
        }



};
