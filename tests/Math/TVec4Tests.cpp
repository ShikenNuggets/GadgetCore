#include <catch2/catch_all.hpp>

#include "GCore/Math/Vector.hpp"

using namespace Gadget;

TEST_CASE("TVec4::TVec4", "[tvec4_constructor]")
{
	const TVec4<double> doubleVec4;
	REQUIRE(doubleVec4.x == 0.0);
	REQUIRE(doubleVec4.y == 0.0);
	REQUIRE(doubleVec4.z == 0.0);
	REQUIRE(doubleVec4.w == 0.0);
}
