#pragma once
#include<iostream>

template<typename T>
class Node{
    public:
        T _value;
        Node* _parent = nullptr, *_left_child = nullptr, *_right_child = nullptr;
    
        Node(T value):_value{value}{}
};

template<typename T>
class BST{
    public:
        Node<T>* _root;

        BST(T root_value):_root{new Node<T>(root_value)}{}

};


