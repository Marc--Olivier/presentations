#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>


struct VertexProperties {
    std::string name;

    VertexProperties() : name("") {}
    VertexProperties(std::string n) : name(n) {}
};

struct EdgeProperties {
    size_t weight;

    EdgeProperties() : weight(0) {}
    EdgeProperties(size_t w) : weight(w) {}
};

using Graph = boost::adjacency_list<
    boost::vecS,        // OutEdgeList
    boost::vecS,        // VertexList
    boost::undirectedS, // Directed
    VertexProperties,   // VertexProperties
    EdgeProperties,     // EdgeProperties
    boost::no_property, // GraphProperties
    boost::listS        // EdgeList
>;

using Vertex = boost::graph_traits<Graph>::vertex_descriptor;
using Edge = boost::graph_traits<Graph>::edge_descriptor;

using MatrixGraph = boost::adjacency_matrix<
    boost::undirectedS, // Directed
    VertexProperties,   // VertexProperties
    EdgeProperties,     // EdgeProperties
    boost::no_property  // GraphProperties
>;
