# tests/CMakeLists.txt
add_executable(testMoplot
	testCurve2D.cpp
)
target_link_libraries(testMoplot
	PUBLIC moplot
)
