cmake_minimum_required(VERSION 3.7)
project(pwd LANGUAGES CXX VERSION 1.0)

find_package(Boost REQUIRED COMPONENTS filesystem system)
add_executable(pwd
	main.cpp
)
# To run pwd, set PATH (Windows), LD_LIBRARY_PATH (Linux),
# or DYLD_LIBRARY_PATH (macOS) to $THIRD_PARTIES/lib
target_link_libraries(pwd PUBLIC
	Boost::boost
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY})
install(TARGETS pwd
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib)
install(FILES
		${Boost_FILESYSTEM_LIBRARY}
		${Boost_SYSTEM_LIBRARY}
	DESTINATION bin)
# Should use BundleUtilities to fix runtime dependencies
include(CPack)
