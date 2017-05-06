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

}
