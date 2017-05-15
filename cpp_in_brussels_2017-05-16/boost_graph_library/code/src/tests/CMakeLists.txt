project(testGraph)

find_package(CatchMain REQUIRED)
find_package(GoogleBenchmarkMain REQUIRED)

add_executable(testMyGraph
        testDijkstra.cpp
        testGraph.cpp
        utils.cpp
        utils.hpp
)
target_link_libraries(testMyGraph
	PUBLIC mygraph CatchMain
)
add_test(NAME testMyGraph COMMAND testMyGraph ~[Skip])
# Note: to run the test, you must have
# the directory containing boost libraries in your PATH

add_executable(benchmarkMyGraph
        benchmarkDijkstra.cpp
)
target_link_libraries(benchmarkMyGraph
        PUBLIC mygraph benchmark::GoogleBenchmarkMain
)
