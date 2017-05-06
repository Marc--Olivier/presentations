cmake_minimum_required(VERSION 3.7)

project(moplot LANGUAGES CXX VERSION 1.0)

add_library(moplot
	curve2D.cpp
	curve2D.hpp
)

add_executable(testMoplot
	testCurve2D.cpp
)

target_link_libraries(testMoplot
	PUBLIC moplot
)

install(TARGETS moplot
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

install(
	FILES curve2D.hpp
	DESTINATION include/moplot
	COMPONENT Devel
)
