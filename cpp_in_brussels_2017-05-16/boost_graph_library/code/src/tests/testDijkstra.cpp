#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <catch.hpp>

#include "tests/utils.hpp"


namespace test {

SCENARIO("Compute shortest paths", "[boost::adjacency_list]") {
    GIVEN("a graph G with:\n"
          "- 5 vertices: V0, V1, V2, V3, V4\n"
          "- 5 edges: V0->V1, V0->V3, V1->V3, V3->V4, V4->V2")
    {
        Graph g;
        buildGraph(g);

        WHEN("Use Dijkstra from V1") {
            const size_t vxNumber = boost::num_vertices(g);
            std::vector<Vertex> predecessors(vxNumber);
            std::vector<size_t> weights(vxNumber);
            auto vxIndexProperty = boost::get(boost::vertex_index, g);
            const Vertex v1 = 1;
            boost::dijkstra_shortest_paths(g, v1,
                    predecessor_map(
                        boost::make_iterator_property_map(predecessors.begin(), vxIndexProperty)).
                    distance_map(
                        boost::make_iterator_property_map(weights.begin(), vxIndexProperty)).
                    weight_map(
                        boost::get(&EdgeProperties::weight, g)).
                    vertex_index_map(
                        vxIndexProperty));

            THEN("Shortest path V1 to V4:\n"
                 "- total weight: 9"
                 "- path: V1 -> V0 -> V3 -> V4")
            {
                CHECK(weights[4] == 9);
                CHECK(predecessors[4] == 3);
                CHECK(predecessors[3] == 0);
                CHECK(predecessors[0] == 1);
            }
        }
    }
}

}
