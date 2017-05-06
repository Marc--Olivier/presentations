#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "Curve2D.hpp"

namespace moplot {
namespace tests {
SCENARIO("Test create Curve2D", "[Curve2D]") {
	GIVEN("None") {
		WHEN("curve = Curve2D{{1.0, 2.0}, {}}") {
			auto curve = Curve2D{{1.0, 2.0}, {}};
		}
	}
}

}
}
