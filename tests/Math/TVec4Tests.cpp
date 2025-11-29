#include <catch2/catch_all.hpp>

#include "GCore/Math/TVec4.hpp"

using namespace Gadget;

TEST_CASE("TVec4::TVec4", "[tvec4_constructor]")
{
	const TVec4<double> doubleVec4;
	REQUIRE(doubleVec4.x == 0.0);
	REQUIRE(doubleVec4.y == 0.0);
	REQUIRE(doubleVec4.z == 0.0);
	REQUIRE(doubleVec4.w == 0.0);
}

TEST_CASE("TVec4::Zero", "[tvec4_zero]")
{
	const TVec4<double> zeroVec = TVec4<double>::Zero();
	REQUIRE(zeroVec.x == 0.0);
	REQUIRE(zeroVec.y == 0.0);
	REQUIRE(zeroVec.z == 0.0);
	REQUIRE(zeroVec.w == 0.0);
}

TEST_CASE("TVec4::Fill", "[tvec4_fill]")
{
	const auto fillTest = TVec4<double>::Fill(0.5);
	REQUIRE(fillTest.x == 0.5);
	REQUIRE(fillTest.y == 0.5);
	REQUIRE(fillTest.z == 0.5);
	REQUIRE(fillTest.w == 0.5);
}

TEST_CASE("TVec4::+", "[tvec4_operator_+]")
{
	const auto plusTest = TVec4<double>(1.0, 2.0, 3.0, 4.0) + TVec4<double>(5.0, 6.0, 7.0, 8.0);
	REQUIRE(plusTest.x == 6.0);
	REQUIRE(plusTest.y == 8.0);
	REQUIRE(plusTest.z == 10.0);
	REQUIRE(plusTest.w == 12.0);
}

TEST_CASE("TVec4::*", "[tvec4_operator_*]")
{
	constexpr auto x = 1.0;
	constexpr auto y = 2.0;
	constexpr auto z = 3.0;
	constexpr auto w = 4.0;

	const auto multTest = TVec4<double>(x, y, z, w) * 5.0;
	REQUIRE(multTest.x == 5.0);
	REQUIRE(multTest.y == 10.0);
	REQUIRE(multTest.z == 15.0);
	REQUIRE(multTest.w == 20.0);

	const auto multTest2 = 5.0 * TVec4<double>(x, y, z, w);
	REQUIRE(multTest.x == multTest2.x);
	REQUIRE(multTest.y == multTest2.y);
	REQUIRE(multTest.z == multTest2.z);
	REQUIRE(multTest.w == multTest2.w);
}

TEST_CASE("TVec4::+=", "[tvec4_operator_+=]")
{
	auto plusEqualTest = TVec4<double>(1.0, 2.0, 3.0, 4.0);
	plusEqualTest += TVec4<double>(5.0, 6.0, 7.0, 8.0);
	REQUIRE(plusEqualTest.x == 6.0);
	REQUIRE(plusEqualTest.y == 8.0);
	REQUIRE(plusEqualTest.z == 10.0);
	REQUIRE(plusEqualTest.w == 12.0);
}

TEST_CASE("TVec4::*=", "[tvec4_operator_*=]")
{
	auto multEqualTest = TVec4<double>(1.0, 2.0, 3.0, 4.0);
	multEqualTest *= 5.0;
	REQUIRE(multEqualTest.x == 5.0);
	REQUIRE(multEqualTest.y == 10.0);
	REQUIRE(multEqualTest.z == 15.0);
	REQUIRE(multEqualTest.w == 20.0);
}

TEST_CASE("TVec4::Dot", "[tvec4_dot]")
{
	const auto dotTestA = TVec4<double>::Dot(TVec4(1.0, 2.0, 3.0, 4.0), TVec4(5.0, 6.0, 7.0, 8.0));
	const auto dotTestB = TVec4<double>::Dot(TVec4(0.0, 0.0, 0.0, 0.0), TVec4(3.0, 2.0, 1.0, 4.0));
	const auto dotTestC = TVec4<double>::Dot(TVec4(-1.0, 2.0, -3.0, 4.0), TVec4(-4.0, 3.0, -2.0, 1.0));

	REQUIRE(Math::IsNear(dotTestA, 70.0));
	REQUIRE(Math::IsNear(dotTestB, 0.0));
	REQUIRE(Math::IsNear(dotTestC, 20.0));
}

TEST_CASE("TVec4::IsValid", "[tvec4_is_valid]")
{
	const auto valid = TVec4<double>(1.0, 2.0, 3.0, 4.0);
	const auto invalid = TVec4<double>(Math::TInfinity<double>, 0.0, -1.0, -2.0);

	REQUIRE(valid.IsValid());
	REQUIRE(!invalid.IsValid());
}
