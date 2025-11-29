#include <catch2/catch_all.hpp>

#include "GCore/Math/TVec2.hpp"

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

TEST_CASE("TVec2::Fill", "[tvec2_fill]")
{
	const auto fillTest = TVec2<double>::Fill(0.5);
	REQUIRE(fillTest.x == 0.5);
	REQUIRE(fillTest.y == 0.5);
}

TEST_CASE("TVec2::+", "[tvec2_operator_+]")
{
	const auto plusTest = TVec2<double>(1.0, 2.0) + TVec2<double>(3.0, 4.0);
	REQUIRE(plusTest.x == 4.0);
	REQUIRE(plusTest.y == 6.0);
}

TEST_CASE("TVec2::*", "[tvec2_operator_*]")
{
	constexpr auto x = 1.0;
	constexpr auto y = 2.0;

	const auto multTest = TVec2<double>(x, y) * 3.0;
	REQUIRE(multTest.x == 3.0);
	REQUIRE(multTest.y == 6.0);

	const auto multTest2 = 3.0 * TVec2<double>(x, y); // Friend multiplication also works
	REQUIRE(multTest.x == multTest2.x);
	REQUIRE(multTest.y == multTest2.y);
}

TEST_CASE("TVec2::+=", "[tvec2_operator_+=]")
{
	auto plusEqualTest = TVec2<double>(1.0, 2.0);
	plusEqualTest += TVec2<double>(3.0, 4.0);
	REQUIRE(plusEqualTest.x == 4.0);
	REQUIRE(plusEqualTest.y == 6.0);
}

TEST_CASE("TVec2::*=", "[tvec2_operator_*=]")
{
	auto multEqualTest = TVec2<double>(1.0, 2.0);
	multEqualTest *= 3.0;
	REQUIRE(multEqualTest.x == 3.0);
	REQUIRE(multEqualTest.y == 6.0);
}

TEST_CASE("TVec2::Dot", "[tvec2_dot]")
{
	const auto dotTestA = TVec2<double>::Dot(TVec2(1.0, 2.0), TVec2(3.0, 4.0));
	const auto dotTestB = TVec2<double>::Dot(TVec2(0.0, 0.0), TVec2(5.0, 7.0));
	const auto dotTestC = TVec2<double>::Dot(TVec2(-1.0, 4.0), TVec2(2.0, -3.0));

	REQUIRE(Math::IsNear(dotTestA, 11.0));
	REQUIRE(Math::IsNear(dotTestB, 0.0));
	REQUIRE(Math::IsNear(dotTestC, -14.0));
}

TEST_CASE("TVec2::IsValid", "[tvec2_is_valid]")
{
	const auto valid = TVec2<double>(1.0, 2.0);
	const auto invalid = TVec2<double>(Math::TInfinity<double>, 0.0);

	REQUIRE(valid.IsValid());
	REQUIRE(!invalid.IsValid());
}
