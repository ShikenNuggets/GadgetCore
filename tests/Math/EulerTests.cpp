#include <catch2/catch_all.hpp>

#include "GCore/Math/Euler.hpp"

using namespace Gadget;

TEST_CASE("TEuler::TEuler", "[teuler_constructor]")
{
	const TEuler<double> euler;
	REQUIRE(euler.x == 0.0);
	REQUIRE(euler.y == 0.0);
	REQUIRE(euler.z == 0.0);
}

TEST_CASE("TEuler::TEuler(TVec3)", "[tvec3_constructor_tvec3]")
{
	const auto doubleVec3 = TVec3<double>(1.0, 2.0, 3.0);
	const auto euler = TEuler<double>(doubleVec3);

	REQUIRE(euler.x == doubleVec3.x);
	REQUIRE(euler.y == doubleVec3.y);
	REQUIRE(euler.z == doubleVec3.z);
}
