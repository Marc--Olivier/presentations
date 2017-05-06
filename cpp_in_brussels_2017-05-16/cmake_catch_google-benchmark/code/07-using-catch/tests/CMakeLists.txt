# tests/CMakeLists.txt
find_package(CatchMain REQUIRED)
add_executable(testMoplot
	testCurve2D.cpp
)
target_link_libraries(testMoplot
	PUBLIC moplot CatchMain
)
add_test(NAME testMoplot COMMAND testMoplot ~[Skip])
