#include <catch.hpp>

#include "Graph.hpp"
#include "tests/utils.hpp"


namespace test {

SCENARIO("create graph", "[boost::adjacency_list]") {
    GIVEN("an empty graph G") {
        Graph g;

        WHEN("add 5 vertices and 5 edges to G") {
            buildGraph(g);

            THEN("G has 5 vertices and 5 edges") {
                CHECK(boost::num_vertices(g) == 5);
                CHECK(boost::num_edges(g) == 5);
            }
        }
    }
}

SCENARIO("get an edge (if exist)", "[boost::adjacency_list]") {
    GIVEN("a graph G with:\n"
          "- 5 vertices: V0, V1, V2, V3, V4\n"
          "- 5 edges: V0->V1, V0->V3, V1->V3, V3->V4, V4->V2")
    {
        Graph g;
        buildGraph(g);

        WHEN("/") {

            THEN("G has an edge between V1 and V3") {
                bool isEdge = false;
                Edge e;
                const Vertex v1 = 1;
                const Vertex v3 = 3;
                boost::tie(e, isEdge) = boost::edge(v1, v3, g);
                CHECK(isEdge == true);
            }

            THEN("G has no edge between V0 and V4") {
                bool isEdge = false;
                Edge e;
                const Vertex v0 = 0;
                const Vertex v4 = 4;
                boost::tie(e, isEdge) = boost::edge(v0, v4, g);
                CHECK(isEdge == false);
            }
        }
    }
}

SCENARIO("edge iterator", "[boost::adjacency_list]") {
    GIVEN("a graph G with:\n"
          "- 5 vertices: V0, V1, V2, V3, V4\n"
          "- 5 edges: (V0,V1), (V0,V3), (V1,V3), (V3,V4), (V4,V2)")
    {
        Graph g;
        buildGraph(g);

        WHEN("compute total edge weight") {
            size_t totalWeight = 0;
            for (const Edge& e : boost::make_iterator_range(edges(g))) {
                totalWeight += g[e].weight;
            }

            THEN("total edge weight == 22") {
                CHECK(totalWeight == 22);
            }
        }
    }
}

}
