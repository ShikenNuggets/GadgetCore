#include <catch2/catch_all.hpp>

#include "Math/Vector.hpp"

TEST_CASE("TVec2 Default Constructor", "[tvec2_default_constructor]")
{
	const GCore::TVec2<double> doubleVec2;
	REQUIRE(doubleVec2.x == 0.0);
	REQUIRE(doubleVec2.y == 0.0);
}

TEST_CASE("TVec2::Zero", "[tvec2::zero]")
{
	const GCore::TVec2<double> zeroVec = GCore::TVec2<double>::Zero();
	REQUIRE(zeroVec.x == 0.0);
	REQUIRE(zeroVec.y == 0.0);
}
