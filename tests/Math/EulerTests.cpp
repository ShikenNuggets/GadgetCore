#include <catch2/catch_all.hpp>

#include "GCore/Math/Euler.hpp"

using namespace Gadget;
using Catch::Approx;

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

TEST_CASE("TEuler::+", "[teuler_operator_+]")
{
	const auto plusTest = TEuler<double>(1.0, 2.0, 3.0) + TEuler<double>(4.0, 5.0, 6.0);
	REQUIRE(plusTest.x == 5.0);
	REQUIRE(plusTest.y == 7.0);
	REQUIRE(plusTest.z == 9.0);
}

TEST_CASE("TEuler::-", "[teuler_operator_-]")
{
	const auto subTest = TEuler<double>(6.0, 5.0, 4.0) - TEuler<double>(3.0, 2.0, 1.0);
	REQUIRE(subTest.x == 3.0);
	REQUIRE(subTest.y == 3.0);
	REQUIRE(subTest.z == 3.0);
}

TEST_CASE("TEuler::*", "[teuler_operator_*]")
{
	constexpr auto x = 1.0;
	constexpr auto y = 2.0;
	constexpr auto z = 3.0;

	const auto multTest = TEuler<double>(x, y, z) * 4.0;
	REQUIRE(multTest.x == 4.0);
	REQUIRE(multTest.y == 8.0);
	REQUIRE(multTest.z == 12.0);

	const auto multTest2 = 4.0 * TEuler<double>(x, y, z);
	REQUIRE(multTest.x == multTest2.x);
	REQUIRE(multTest.y == multTest2.y);
	REQUIRE(multTest.z == multTest2.z);
}

TEST_CASE("TEuler::Lerp", "[teuler_lerp]")
{
	const auto a = TEuler<double>(0.0, 1.0, 2.0);
	const auto b = TEuler<double>(4.0, 5.0, 6.0);
	const auto lerpTest = TEuler<double>::Lerp(a, b, 0.5);

	REQUIRE(lerpTest.x == Approx(2.0));
	REQUIRE(lerpTest.y == Approx(3.0));
	REQUIRE(lerpTest.z == Approx(4.0));
}

TEST_CASE("TEuler::IsValid", "[teuler_is_valid]")
{
	const auto valid = TEuler<double>(1.0, 2.0, 3.0);
	const auto invalid = TEuler<double>(Math::TInfinity<double>, 0.0, -1.0);

	REQUIRE(valid.IsValid());
	REQUIRE(!invalid.IsValid());
}
