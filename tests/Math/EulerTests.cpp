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

TEST_CASE("TEuler::TEuler(TVec3)", "[teuler_constructor_tvec3]")
{
	const auto doubleVec3 = TVec3<double>(1.0, 2.0, 3.0);
	const auto euler = TEuler<double>(doubleVec3);

	REQUIRE(euler.x == doubleVec3.x);
	REQUIRE(euler.y == doubleVec3.y);
	REQUIRE(euler.z == doubleVec3.z);
}

TEST_CASE("TEuler::IsValid", "[teuler_is_valid]")
{
	const auto valid = TEuler<double>(1.0, 2.0, 3.0);
	const auto invalid = TEuler<double>(Math::TInfinity<double>, 0.0, -1.0);

	REQUIRE(valid.IsValid());
	REQUIRE(!invalid.IsValid());
}
