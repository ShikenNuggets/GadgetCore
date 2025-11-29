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

TEST_CASE("TVec3::Zero", "[tvec3_zero]")
{
	const TVec3<double> zeroVec = TVec3<double>::Zero();
	REQUIRE(zeroVec.x == 0.0);
	REQUIRE(zeroVec.y == 0.0);
	REQUIRE(zeroVec.z == 0.0);
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

TEST_CASE("TVec3::-", "[tvec3_operator_-]")
{
	const auto subTest = TVec3<double>(6.0, 5.0, 4.0) - TVec3<double>(3.0, 2.0, 1.0);
	REQUIRE(subTest.x == 3.0);
	REQUIRE(subTest.y == 3.0);
	REQUIRE(subTest.z == 3.0);
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

TEST_CASE("TVec3::/", "[tvec3_operator_/]")
{
	const auto divTest = TVec3<double>(3.0, 6.0, 9.0) / 3.0;
	REQUIRE(divTest.x == 1.0);
	REQUIRE(divTest.y == 2.0);
	REQUIRE(divTest.z == 3.0);
}

TEST_CASE("TVec3::+=", "[tvec3_operator_+=]")
{
	auto plusEqualTest = TVec3<double>(1.0, 2.0, 3.0);
	plusEqualTest += TVec3<double>(4.0, 5.0, 6.0);
	REQUIRE(plusEqualTest.x == 5.0);
	REQUIRE(plusEqualTest.y == 7.0);
	REQUIRE(plusEqualTest.z == 9.0);
}

TEST_CASE("TVec3::-=", "[tvec3_operator_-=]")
{
	auto subEqualTest = TVec3<double>(6.0, 5.0, 4.0);
	subEqualTest -= TVec3<double>(3.0, 2.0, 1.0);
	REQUIRE(subEqualTest.x == 3.0);
	REQUIRE(subEqualTest.y == 3.0);
	REQUIRE(subEqualTest.z == 3.0);
}

TEST_CASE("TVec3::*=", "[tvec3_operator_*=]")
{
	auto multEqualTest = TVec3<double>(1.0, 2.0, 3.0);
	multEqualTest *= 4.0;
	REQUIRE(multEqualTest.x == 4.0);
	REQUIRE(multEqualTest.y == 8.0);
	REQUIRE(multEqualTest.z == 12.0);
}

TEST_CASE("TVec3::/=", "[tvec3_operator_/=]")
{
	auto divTest = TVec3<double>(3.0, 6.0, 9.0);
	divTest /= 3.0;
	REQUIRE(divTest.x == 1.0);
	REQUIRE(divTest.y == 2.0);
	REQUIRE(divTest.z == 3.0);
}

TEST_CASE("TVec3::SquaredMagnitude", "[tvec3_squared_magnitude]")
{
	auto magTest = TVec3<double>(4.0, 4.0, 4.0);
	REQUIRE(magTest.SquaredMagnitude() == 48.0);
}

TEST_CASE("TVec3::Magnitude", "[tvec3_magnitude]")
{
	auto magTest = TVec3<double>(4.0, 4.0, 4.0);
	REQUIRE(magTest.Magnitude() == Math::Sqrt(48.0));

	auto magTest2 = TVec3<double>(0.0, 0.0, 0.0);
	REQUIRE(magTest2.Magnitude() == 0.0);
}

TEST_CASE("TVec3::Normal", "[tvec3_normal]")
{
	auto normalTest = TVec3<double>(4.0, 4.0, 4.0);
	auto normal = normalTest.Normal();
	const auto expected = normalTest / Math::Sqrt(48.0);
	REQUIRE(Math::IsNear(normal.Magnitude(), 1.0));
	REQUIRE(Math::IsNear(normal.x, expected.x));
	REQUIRE(Math::IsNear(normal.y, expected.y));
	REQUIRE(Math::IsNear(normal.z, expected.z));
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

TEST_CASE("TVec3::Lerp", "[tvec3_lerp]")
{
	const auto a = TVec3<double>(0.0, 1.0, 2.0);
	const auto b = TVec3<double>(4.0, 5.0, 6.0);
	const auto lerpTest = TVec3<double>::Lerp(a, b, 0.5);

	REQUIRE(Math::IsNear(lerpTest.x, 2.0));
	REQUIRE(Math::IsNear(lerpTest.y, 3.0));
	REQUIRE(Math::IsNear(lerpTest.z, 4.0));
}

TEST_CASE("TVec3::IsNear", "[tvec3_is_near]")
{
	const auto testA = TVec3<double>(1.0, 2.0, 3.0);
	const auto testB = TVec3<double>(1.0, 2.0, 3.0);
	const auto testC = TVec3<double>(1.0001, 2.0001, 3.1);

	REQUIRE(testA.IsNear(testA));
	REQUIRE(testA.IsNear(testB));
	REQUIRE(!testA.IsNear(testC));

	REQUIRE(testB.IsNear(testB));
	REQUIRE(!testB.IsNear(testC));

	REQUIRE(testC.IsNear(testC));
}

TEST_CASE("TVec3::IsValid", "[tvec3_is_valid]")
{
	const auto valid = TVec3<double>(1.0, 2.0, 3.0);
	const auto invalid = TVec3<double>(Math::TInfinity<double>, 0.0, -1.0);

	REQUIRE(valid.IsValid());
	REQUIRE(!invalid.IsValid());
}
