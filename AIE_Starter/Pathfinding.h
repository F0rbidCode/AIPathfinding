#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

namespace AIForGames
{
    struct Node;

    struct Edge {
        Edge() { target = nullptr; cost = 0; }
        Edge(Node* _target, float _cost) : target(_target), cost(_cost) {}
        Node* target;
        float cost;
    };

    struct Node {
        glm::vec2 position; //current position
        std::vector<Edge> connections;
        
        Node() { previous = NULL; } //default constructor
        Node(float x, float y) { position.x = x; position.y = y, previous = NULL; }; //constructor to take in floats
        void ConnectTo(Node* other, float cost);

        //variables used for pathfinding
        float gScore;
        Node* previous;

        //used for A*
        float hScore;
        float fScore;        
    };

    std::vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);
    std::vector<Node*> AStarSearch(Node* startNode, Node* endNode);

    //function to compare the gScore of given nodes
    bool CompareGScore(Node*& first, Node*& second);

    //function to compare the fScore of given nodes
    bool CompareFScore(Node*& first, Node*& second);

    //function to calculate the hScore
    float Heuristic(Node* current, Node* end);

    
}
