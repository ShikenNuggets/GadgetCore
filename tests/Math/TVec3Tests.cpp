#include <catch2/catch_all.hpp>

#include "GCore/Math/Vector.hpp"

using namespace Gadget;

TEST_CASE("TVec3::TVec3", "[tvec3_constructor]")
{
	const TVec3<double> doubleVec3;
	REQUIRE(doubleVec3.x == 0.0);
	REQUIRE(doubleVec3.y == 0.0);
	REQUIRE(doubleVec3.z == 0.0);
}
