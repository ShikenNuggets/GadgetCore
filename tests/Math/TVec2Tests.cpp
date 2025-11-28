#include <catch2/catch_all.hpp>

#include "GCore/Math/Vector.hpp"

using namespace Gadget;

TEST_CASE("TVec2::TVec2", "[tvec2_constructor]")
{
	const TVec2<double> doubleVec2;
	REQUIRE(doubleVec2.x == 0.0);
	REQUIRE(doubleVec2.y == 0.0);
}

TEST_CASE("TVec2::Zero", "[tvec2_zero]")
{
	const TVec2<double> zeroVec = TVec2<double>::Zero();
	REQUIRE(zeroVec.x == 0.0);
	REQUIRE(zeroVec.y == 0.0);
}
