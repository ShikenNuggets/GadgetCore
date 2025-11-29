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

TEST_CASE("TVec3::*", "[tvec3_operator_*]")
{
	constexpr auto x = 1.0;
	constexpr auto y = 2.0;
	constexpr auto z = 3.0;

	const auto multTest = TVec3<double>(x, y, z) * 4.0;
	REQUIRE(multTest.x == 4.0);
	REQUIRE(multTest.y == 8.0);
	REQUIRE(multTest.z == 12.0);

	const auto multTest2 = 4.0 * TVec3<double>(x, y, z);
	REQUIRE(multTest.x == multTest2.x);
	REQUIRE(multTest.y == multTest2.y);
	REQUIRE(multTest.z == multTest2.z);
}

TEST_CASE("TVec3::+=", "[tvec3_operator_+=]")
{
	auto plusEqualTest = TVec3<double>(1.0, 2.0, 3.0);
	plusEqualTest += TVec3<double>(4.0, 5.0, 6.0);
	REQUIRE(plusEqualTest.x == 5.0);
	REQUIRE(plusEqualTest.y == 7.0);
	REQUIRE(plusEqualTest.z == 9.0);
}

TEST_CASE("TVec3::*=", "[tvec3_operator_*=]")
{
	auto multEqualTest = TVec3<double>(1.0, 2.0, 3.0);
	multEqualTest *= 4.0;
	REQUIRE(multEqualTest.x == 4.0);
	REQUIRE(multEqualTest.y == 8.0);
	REQUIRE(multEqualTest.z == 12.0);
}

TEST_CASE("TVec3::Dot", "[tvec3_dot]")
{
	const auto dotTestA = TVec3<double>::Dot(TVec3(1.0, 2.0, 3.0), TVec3(4.0, 5.0, 6.0));
	const auto dotTestB = TVec3<double>::Dot(TVec3(0.0, 0.0, 0.0), TVec3(9.0, 8.0, 7.0));
	const auto dotTestC = TVec3<double>::Dot(TVec3(-1.0, 2.0, -3.0), TVec3(4.0, -5.0, 6.0));

	REQUIRE(Math::IsNear(dotTestA, 32.0));
	REQUIRE(Math::IsNear(dotTestB, 0.0));
	REQUIRE(Math::IsNear(dotTestC, -32.0));
}

TEST_CASE("TVec3::Cross", "[tvec3_cross]")
{
	// Basic axis-vector test
	{
		const auto a = TVec3<double>(1.0, 0.0, 0.0);
		const auto b = TVec3<double>(0.0, 1.0, 0.0);
		const auto c = TVec3<double>::Cross(a, b);

		REQUIRE(c.x == 0.0);
		REQUIRE(c.y == 0.0);
		REQUIRE(c.z == 1.0);
	}

	// Known computed value
	{
		const auto a = TVec3<double>(1.0, 2.0, 3.0);
		const auto b = TVec3<double>(4.0, 5.0, 6.0);
		const auto c = TVec3<double>::Cross(a, b);

		REQUIRE(c.x == -3.0);	// 2*6 - 3*5
		REQUIRE(c.y == 6.0);	// 3*4 - 1*6
		REQUIRE(c.z == -3.0);	// 1*5 - 2*4
	}

	// Anti-commutativity: a × b = -(b × a)
	{
		const auto a = TVec3<double>(3.0, -2.0, 5.0);
		const auto b = TVec3<double>(-1.0, 4.0, 2.0);

		const auto c1 = TVec3<double>::Cross(a, b);
		const auto c2 = TVec3<double>::Cross(b, a);

		REQUIRE(c1.x == -c2.x);
		REQUIRE(c1.y == -c2.y);
		REQUIRE(c1.z == -c2.z);
	}

	// Vector crossed with itself yields zero
	{
		const auto a = TVec3<double>(4.0, -3.0, 1.0);
		const auto c = TVec3<double>::Cross(a, a);

		REQUIRE(c.x == 0.0);
		REQUIRE(c.y == 0.0);
		REQUIRE(c.z == 0.0);
	}

	// Orthogonality: dot(a × b, a) == 0 and dot(a × b, b) == 0
	{
		const auto a = TVec3<double>(2.0, 1.0, 3.0);
		const auto b = TVec3<double>(-1.0, 4.0, 2.0);
		const auto c = TVec3<double>::Cross(a, b);

		const auto dot1 = TVec3<double>::Dot(a, c);
		const auto dot2 = TVec3<double>::Dot(b, c);

		REQUIRE(Math::IsNearZero(dot1));
		REQUIRE(Math::IsNearZero(dot2));
	}
}

TEST_CASE("TVec3::IsValid", "[tvec3_is_valid]")
{
	const auto valid = TVec3<double>(1.0, 2.0, 3.0);
	const auto invalid = TVec3<double>(Math::TInfinity<double>, 0.0, -1.0);

	REQUIRE(valid.IsValid());
	REQUIRE(!invalid.IsValid());
}
