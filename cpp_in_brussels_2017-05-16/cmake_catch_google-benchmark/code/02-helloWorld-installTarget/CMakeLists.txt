cmake_minimum_required(VERSION 3.7)

project(hwProj LANGUAGES CXX VERSION 1.0)

add_executable(helloWorld
	main.cpp
)

install(TARGETS helloWorld
	RUNTIME DESTINATION bin
)
