#include <benchmark/benchmark.h>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include "Graph.hpp"
#include "tests/utils.hpp"


namespace benchmark {

template<class GraphType>
void buildFullGraph(GraphType& g, size_t vertexNb) {
    for (size_t i=0; i < vertexNb; ++i) {
        boost::add_vertex(g);
    }
    for (size_t i=0; i < vertexNb; ++i) {
        for (size_t j=0; j < vertexNb; ++j) {
            boost::add_edge(i, j, EdgeProperties(1), g);
        }
    }
}

template<class GraphType>
void runDijkstra(const GraphType& g, const Vertex& from) {
    const size_t vxNumber = boost::num_vertices(g);
    std::vector<Vertex> predecessors(vxNumber);
    std::vector<size_t> weights(vxNumber);
    auto vxIndexProperty = boost::get(boost::vertex_index, g);
    boost::dijkstra_shortest_paths(g, from,
            predecessor_map(
                boost::make_iterator_property_map(predecessors.begin(), vxIndexProperty)).
            distance_map(
                boost::make_iterator_property_map(weights.begin(), vxIndexProperty)).
            weight_map(
                boost::get(&EdgeProperties::weight, g)).
            vertex_index_map(
                vxIndexProperty));
}

void BM_list_graph_dijkstra(benchmark::State& state) {
    const size_t vertexNb = state.range(0);
    Graph g(vertexNb);
    buildFullGraph(g, vertexNb);
    const Vertex v0 = 0;
    while (state.KeepRunning()) {
        runDijkstra(g, v0);
    }
}

void BM_matrix_graph_dijkstra(benchmark::State& state) {
    const size_t vertexNb = state.range(0);
    MatrixGraph g(vertexNb);
    buildFullGraph(g, vertexNb);
    const Vertex v0 = 0;
    while (state.KeepRunning()) {
        runDijkstra(g, v0);
    }
}

BENCHMARK(BM_list_graph_dijkstra)->RangeMultiplier(2)->Range(8, 1024);
BENCHMARK(BM_matrix_graph_dijkstra)->RangeMultiplier(2)->Range(8, 1024);

}
