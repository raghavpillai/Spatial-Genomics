#include<iostream>
#include<string>
#include "Node.h"
#include "CellData.h"

using std::cout;

// Default constructor
// remember to initialize next to nullptr
Node::Node() {
    next = nullptr;
} 

// Parameterized constructor
// remember to initialize next to nullptr
Node::Node(std::string id, int fov, double volume, double center_x, double center_y, double min_x, double max_x, double min_y, double max_y) {
    this.id = id;
    this.fov = fov;
}

