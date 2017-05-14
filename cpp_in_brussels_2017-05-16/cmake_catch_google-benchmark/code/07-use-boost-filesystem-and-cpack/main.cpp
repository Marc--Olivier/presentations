#include <boost/filesystem.hpp>
#include <iostream>

int main(int argc, const char* argv[]) {
	auto curPath = boost::filesystem::path(".");
	std::cout << boost::filesystem::canonical(curPath) << std::endl;
	return 0;
}
