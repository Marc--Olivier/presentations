//#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "Curve2D.hpp"

// https://github.com/philsquared/Catch/blob/master/docs/tostring.md#catchstringmaker-specialisation
namespace Catch {
template<> struct StringMaker<moplot::Line> {
	static std::string convert(moplot::Line const& line) {
		std::ostringstream ss;
		ss << "{x1=" << line.x1 << ", y1=" << line.y1
			<< ", x2=" << line.x2 << ", y2=" << line.y2 << "}";
		return ss.str();
	}
};
}

namespace moplot {
namespace tests {

// https://github.com/philsquared/Catch/blob/master/docs/matchers.md
class MatcherLineEquals : public Catch::MatcherBase<Line> {
	const Line& line_;
public:
	MatcherLineEquals(Line const& line) : line_(line) {}
	virtual bool match(Line const& rhs) const override {
		return rhs.x1 == Approx(line_.x1) &&
			rhs.y1 == Approx(line_.y1) &&
			rhs.x2 == Approx(line_.x2) &&
			rhs.y2 == Approx(line_.y2);
	}
	virtual std::string describe() const override {
		return "!= " + Catch::toString(line_);
	}
};
inline auto Equals(Line const& line) {
	return MatcherLineEquals(line);
}

SCENARIO("Test create Curve2D", "[Curve2D]") {
	GIVEN("None") {
		WHEN("curve = Curve2D{{1.0, 2.0}, {}}") {
			THEN("Throws std::invalid_argument("
					"\"Invalid sizes: 2 xvals vs. 0 yvals\")") {
				CHECK_THROWS_AS(Curve2D({1.0, 2.0}, {}),
					std::invalid_argument);
				CHECK_THROWS_WITH(Curve2D({1.0, 2.0}, {}),
					"Invalid sizes: 2 xvals vs. 0 yvals");
			}
		}
	}
}

SCENARIO("Intersection line/rectangle", "[Curve2D]") {
	GIVEN("rect = Rect{xmin=100, xmax=500, ymin=10, ymax=60}") {
		auto rect = Rect{100.0, 500.0, 10.0, 60.0};
		WHEN("intersection = intersect(rect, Line{x1=0, y1=0, x2=90, y2=100})") {
			auto intersection = intersect(rect, Line{0.0, 0.0, 90.0, 100.0});
			THEN("intersection.empty") {
				CHECK(intersection.empty);
			}
		}
		WHEN("intersection = intersect(rect, Line{x1=350, y1=20, x2=120, y2=40})") {
			auto intersection = intersect(rect, Line{350.0, 20.0, 120.0, 40.0});
			THEN("!intersection.empty and intersection.line == Line{x1=350, y1=20, x2=120, y2=40}") {
				REQUIRE(!intersection.empty);
				CHECK(intersection.line.x1 == Approx(350.0));
				CHECK(intersection.line.y1 == Approx(20.0));
				CHECK(intersection.line.x2 == Approx(120.0));
				CHECK(intersection.line.y2 == Approx(40.0));
			}
			THEN("!intersection.empty and"
					"intersection.line == Line{x1=350, y1=20, x2=120, y2=40}") {
				REQUIRE(!intersection.empty);
				CHECK_THAT(intersection.line, Equals(Line{350.0, 20.0, 120.0, 40.0}));
			}
		}
		WHEN("intersection = intersect(rect, Line{x1=350, y1=80, x2=350, y2=0})") {
			auto intersection = intersect(rect, Line{350.0, 80.0, 350.0, 0.0});
			THEN("!intersection.empty and"
					"intersection.line == Line{x1=350, y1=60, x2=350, y2=10}") {
				REQUIRE(!intersection.empty);
				CHECK_THAT(intersection.line, Equals(Line{350.0, 60.0, 350.0, 10.0}));
			}
		}
		WHEN("intersection = intersect(rect, Line{x1=0, y1=5, x2=200, y2=25})") {
			auto intersection = intersect(rect, Line{0.0, 5.0, 200.0, 25.0});
			THEN("!intersection.empty and"
					"intersection.line == Line{x1=100, y1=15, x2=200, y2=25}") {
				REQUIRE(!intersection.empty);
				CHECK_THAT(intersection.line, Equals(Line{100.0, 15.0, 200.0, 25.0}));
			}
		}
		WHEN("intersection = intersect(rect, Line{x1=0, y1=55, x2=200, y2=75})") {
			auto intersection = intersect(rect, Line{0.0, 55.0, 200.0, 75.0});
			THEN("intersection.empty") {
				REQUIRE(intersection.empty);
			}
		}
	}
}

}
}
