#include <catch2/catch_all.hpp>

#include "GCore/Math/TVec3.hpp"

using namespace Gadget;

TEST_CASE("TVec3::TVec3", "[tvec3_constructor]")
{
	const TVec3<double> doubleVec3;
	REQUIRE(doubleVec3.x == 0.0);
	REQUIRE(doubleVec3.y == 0.0);
	REQUIRE(doubleVec3.z == 0.0);
}

TEST_CASE("TVec3::Fill", "[tvec3_fill]")
{
	const auto fillTest = TVec3<double>::Fill(0.5);
	REQUIRE(fillTest.x == 0.5);
	REQUIRE(fillTest.y == 0.5);
	REQUIRE(fillTest.z == 0.5);
}

TEST_CASE("TVec3::+", "[tvec3_operator_+]")
{
	const auto plusTest = TVec3<double>(1.0, 2.0, 3.0) + TVec3<double>(4.0, 5.0, 6.0);
	REQUIRE(plusTest.x == 5.0);
	REQUIRE(plusTest.y == 7.0);
	REQUIRE(plusTest.z == 9.0);
}

TEST_CASE("TVec3::+=", "[tvec3_operator_+=]")
{
	auto plusEqualTest = TVec3<double>(1.0, 2.0, 3.0);
	plusEqualTest += TVec3<double>(4.0, 5.0, 6.0);
	REQUIRE(plusEqualTest.x == 5.0);
	REQUIRE(plusEqualTest.y == 7.0);
	REQUIRE(plusEqualTest.z == 9.0);
}

TEST_CASE("TVec3::IsValid", "[tvec3_is_valid]")
{
	const auto valid = TVec3<double>(1.0, 2.0, 3.0);
	const auto invalid = TVec3<double>(Math::TInfinity<double>, 0.0, -1.0);

	REQUIRE(valid.IsValid());
	REQUIRE(!invalid.IsValid());
}
