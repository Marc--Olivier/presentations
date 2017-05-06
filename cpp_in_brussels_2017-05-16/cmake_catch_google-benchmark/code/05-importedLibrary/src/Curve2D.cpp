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

}
