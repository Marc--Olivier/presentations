# src/CMakeLists.txt
add_library(moplot
	curve2D.cpp
	curve2D.hpp
)
target_include_directories(moplot PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>  
	$<INSTALL_INTERFACE:include/moplot>
)
install(TARGETS moplot EXPORT moplotConfig
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	INCLUDES DESTINATION include
)
# https://cmake.org/cmake/help/latest/command/install.html
install(FILES curve2D.hpp
	DESTINATION include/moplot
	COMPONENT Devel)
include(CMakePackageConfigHelpers)
install(EXPORT moplotConfig
	FILE moplotConfig.cmake
	DESTINATION lib/cmake/moplot)
