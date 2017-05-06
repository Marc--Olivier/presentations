# src/CMakeLists.txt
add_library(moplot
	curve2D.cpp
	curve2D.hpp
)
target_include_directories(moplot
	PUBLIC .
)
install(TARGETS moplot
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	INCLUDES DESTINATION include
)
install(
	FILES curve2D.hpp
	DESTINATION include/moplot
	COMPONENT Devel
)
