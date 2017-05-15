#include "tests/utils.hpp"


namespace test {

void buildGraph(Graph& g) {
    Vertex v0 = boost::add_vertex(g);
    g[v0].name = "v0";
    Vertex v1 = boost::add_vertex(g);
    g[v1].name = "v1";

    Vertex v2 = boost::add_vertex(VertexProperties("v2"), g);
    Vertex v3 = boost::add_vertex(VertexProperties("v3"), g);
    Vertex v4 = boost::add_vertex(VertexProperties("v4"), g);

    bool success = false;
    Edge e;
    boost::tie(e, success) = boost::add_edge(v0, v1, g);
    g[e].weight = 2;
    boost::tie(e, success) = boost::add_edge(v0, v3, g);
    g[e].weight = 4;

    boost::tie(e, success) = add_edge(v1, v3, EdgeProperties(8), g);
    boost::tie(e, success) = add_edge(v3, v4, EdgeProperties(3), g);
    boost::tie(e, success) = add_edge(v4, v2, EdgeProperties(5), g);
}

}
