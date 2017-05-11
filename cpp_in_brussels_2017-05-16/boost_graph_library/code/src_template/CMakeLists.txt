cmake_minimum_required(VERSION 3.7)
project(mygraph LANGUAGES CXX VERSION 1.0)
set(CMAKE_CXX_STANDARD 14)
enable_testing()

# from build_aux dir, run
# cmake -G"CodeBlocks - Ninja" -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-std=c++1z" -DCMAKE_PREFIX_PATH=$THIRD_PARTIES ../src_template
find_package(Boost REQUIRED COMPONENTS graph regex)

add_library(mygraph
	Graph.cpp
	Graph.hpp
)
target_link_libraries(mygraph
	PUBLIC Boost::boost ${Boost_GRAPH_LIBRARY}
)
target_include_directories(mygraph
	PUBLIC .
)

add_subdirectory(tests)
