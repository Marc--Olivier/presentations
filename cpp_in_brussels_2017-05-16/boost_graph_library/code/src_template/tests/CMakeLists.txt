project(testGraph)

find_package(CatchMain REQUIRED)
find_package(GoogleBenchmarkMain REQUIRED)

add_executable(testMyGraph
	testGraph.cpp
)
target_link_libraries(testMyGraph
	PUBLIC mygraph CatchMain
)
add_test(NAME testMyGraph COMMAND testMyGraph ~[Skip])
# Note: to run the test, you must have
# the directory containing boost libraries in your PATH
