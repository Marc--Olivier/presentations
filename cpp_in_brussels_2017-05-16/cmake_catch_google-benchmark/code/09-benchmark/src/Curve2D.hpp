#pragma once

#include <vector>

namespace moplot {

class Curve2D {
public:
	Curve2D(std::vector<double>&& xvals, std::vector<double>&& yvals);
	const auto& xvals() const {
		return xvals_;
	}
	const auto& yvals() const {
		return yvals_;
	}
private:
	std::vector<double> xvals_;
	std::vector<double> yvals_;
};

struct Rect {
	double xmin;
	double xmax;
	double ymin;
	double ymax;
};

struct Line {
	double x1;
	double y1;
	double x2;
	double y2;
};

struct Intersection {
	Line line;
	bool empty;
};

Intersection intersect(const Rect& rect, const Line& line);

}
