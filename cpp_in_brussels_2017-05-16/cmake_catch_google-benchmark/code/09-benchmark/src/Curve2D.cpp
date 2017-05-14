#include "curve2D.hpp"

#include <stdexcept>
#include <string>

namespace moplot {

Curve2D::Curve2D(std::vector<double>&& xvals, std::vector<double>&& yvals)
	: xvals_(std::move(xvals))
	, yvals_(std::move(yvals))
{
	if(xvals_.size() != yvals_.size()) {
		throw std::invalid_argument("Invalid sizes: "
			+ std::to_string(xvals_.size()) + " xvals vs. "
			+ std::to_string(yvals_.size()) + " yvals");
	}
}

Intersection emptyIntersection() {
	return Intersection{Line{0.0, 0.0, 0.0, 0.0}, true};
}

Intersection lineIntersection(const Line& intersection) {
	return Intersection{intersection, false};
}

inline bool swapAndCheckIntersection(double& x1, double& x2, double& y1, double& y2,
		const double& rectXMin, const double& rectXMax, bool& isSwapped) {
	if(x1 > x2) {
		isSwapped = !isSwapped;
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	if(x2 < rectXMin || x1 > rectXMax) {
		return false;
	}
	return true;
}

inline bool projectLine(double& x1, double& x2, double& y1, double& y2,
		const double& rectXMin, const double& rectXMax,
		const double& rectYMin, const double& rectYMax, bool& isSwapped) {
	if(!swapAndCheckIntersection(x1, x2, y1, y2,
			rectXMin, rectXMax, isSwapped)) {
		return false;
	}
	auto startLeft = (x1 < rectXMin);
	auto endRight = (x2 > rectXMax);
	if(startLeft || endRight) {
		// Line equation: y = slope * x + offset
		auto slope = (y2-y1)/(x2-x1);
		auto offset = y1 - slope*x1;
		if(startLeft) {
			x1 = rectXMin;
			y1 = slope * x1 + offset;
		}
		if(endRight) {
			x2 = rectXMax;
			y2 = slope * x2 + offset;
		}
	}
	return true;

}

Intersection intersect(const Rect& rect, const Line& line) {
	auto x1 = line.x1;
	auto x2 = line.x2;
	auto y1 = line.y1;
	auto y2 = line.y2;
	bool swapped = false;
	auto succeed = projectLine(x1, x2, y1, y2,
		rect.xmin, rect.xmax, rect.ymin, rect.ymax, swapped);
	if(!succeed) {
		return emptyIntersection();
	}
	succeed = projectLine(y1, y2, x1, x2,
		rect.ymin, rect.ymax, rect.xmin, rect.xmax, swapped);
	if(!succeed) {
		return emptyIntersection();
	}
	succeed = swapAndCheckIntersection(x1, x2, y1, y2,
		rect.xmin, rect.xmax, swapped);
	if(!succeed) {
		return emptyIntersection();
	}
	return lineIntersection(swapped? Line{x2, y2, x1, y1} :
		Line{x1, y1, x2, y2});
}

}
