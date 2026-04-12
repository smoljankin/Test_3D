#pragma once

#include <vector>

struct Vertex {
    double x;
    double y;
    double z;
};

struct Normale {
    double x;
    double y;
    double z;
};

struct Face {
    Vertex v1;
    Vertex v2;
    Vertex v3;
    Normale vn1;
    Normale vn2;
    Normale vn3;
};

struct Model {
    std::vector<Face> faces;
};