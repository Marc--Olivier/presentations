#include <benchmark/benchmark.h>

#include "Curve2D.hpp"

#include <iostream>
#include <random>

namespace moplot {
namespace bm {



void displayMinMax(const std::vector<Line>& lines) {
	if(lines.empty()) {
		return;
	}
	const auto& l = lines.front();
	std::pair<double, double> xMinMax = std::minmax(l.x1, l.x2);
	std::pair<double, double> yMinMax = std::minmax(l.y1, l.y2);
	for(const auto& line : lines) {
		auto xLineMinMax = std::minmax(line.x1, line.x2);
		auto yLineMinMax = std::minmax(line.y1, line.y2);
		if(xLineMinMax.first < xMinMax.first) {
			xMinMax.first = xLineMinMax.first; 
		}
		if(xLineMinMax.second > xMinMax.second) {
			xMinMax.second = xLineMinMax.second; 
		}
		if(yLineMinMax.first < yMinMax.first) {
			yMinMax.first = yLineMinMax.first; 
		}
		if(yLineMinMax.second > yMinMax.second) {
			yMinMax.second = yLineMinMax.second; 
		}
	}
	std::cout << "x in [" << xMinMax.first << ", " << xMinMax.second
		<< "]. y in [" << yMinMax.first << ", " << yMinMax.second << "]."<< std::endl;
}

std::vector<Line> generateLines(size_t count, const Rect& rect) {
	int seed = 42;
	std::default_random_engine randEngine(seed);
	std::uniform_int_distribution<double> xDistr(rect.xmin, rect.xmax);
	std::uniform_int_distribution<double> yDistr(rect.ymin, rect.ymax);
	std::vector<Line> lines;
	lines.reserve(count);
	for(size_t i = 0; i < count; ++i) {
		lines.push_back(Line{
			xDistr(randEngine), yDistr(randEngine), 
			xDistr(randEngine), yDistr(randEngine)});
	}
	//displayMinMax(lines);
	return lines;
}

void BM_Intersect(benchmark::State& state) {
	size_t count = state.range(0);
	auto lines = generateLines(
		count, Rect{0.0, 1000.0, 0.0, 100.0});
	Rect rect{200.0, 800.0, 20.0, 80.0};
	while (state.KeepRunning()) {
		for(const auto& line : lines) {
			intersect(rect, line);
		}
	}
}
BENCHMARK(BM_Intersect)->RangeMultiplier(2)->Range(1 << 10, 1 << 12);


}
}
