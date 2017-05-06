# tests/CMakeLists.txt
find_file(CatchHeader catch/catch.hpp)
if(NOT CatchHeader)
	message(FATAL_ERROR "Could not find Catch header: ${CatchHeader}")
endif()
get_filename_component(CatchIncludeDir ${CatchHeader} DIRECTORY)
message(STATUS "Catch found in ${CatchIncludeDir}")
add_library(catch INTERFACE IMPORTED GLOBAL)
set_property(TARGET catch PROPERTY
	INTERFACE_INCLUDE_DIRECTORIES ${CatchIncludeDir})

add_executable(testMoplot
	testCurve2D.cpp
)
target_link_libraries(testMoplot
	PUBLIC moplot catch
)
add_test(NAME testMoplot COMMAND testMoplot ~[Skip])
