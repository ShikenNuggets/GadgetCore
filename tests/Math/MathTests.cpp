#include <iostream>

#include <catch2/catch_all.hpp>

#include "GCore/Math/Math.hpp"

using namespace GCore;

TEST_CASE("Math::IsNearZero", "[math_is_near_zero]")
{
	REQUIRE(Math::IsNearZero(0.0));
	REQUIRE(Math::IsNearZero(-0.0));
	REQUIRE(Math::IsNearZero(0.0f));
	REQUIRE(Math::IsNearZero(-0.0f));

	REQUIRE_FALSE(Math::IsNearZero(0.001));
	REQUIRE_FALSE(Math::IsNearZero(-0.001));
	REQUIRE_FALSE(Math::IsNearZero(1.0));
	REQUIRE_FALSE(Math::IsNearZero(-1.0));
	
	REQUIRE_FALSE(Math::IsNearZero(0.001f));
	REQUIRE_FALSE(Math::IsNearZero(-0.001f));
	REQUIRE_FALSE(Math::IsNearZero(1.0f));
	REQUIRE_FALSE(Math::IsNearZero(-1.0f));

	REQUIRE_FALSE(Math::IsNearZero(Math::TInfinity<float>));
	REQUIRE_FALSE(Math::IsNearZero(Math::TInfinity<double>));
	REQUIRE_FALSE(Math::IsNearZero(Math::TInfinity<long double>));

	REQUIRE(Math::IsNearZero(std::numeric_limits<float>::denorm_min()));
	REQUIRE(Math::IsNearZero(std::numeric_limits<double>::denorm_min()));
	REQUIRE(Math::IsNearZero(std::numeric_limits<long double>::denorm_min()));

	REQUIRE_FALSE(Math::IsNearZero(std::numeric_limits<float>::quiet_NaN()));
	REQUIRE_FALSE(Math::IsNearZero(std::numeric_limits<double>::quiet_NaN()));
	REQUIRE_FALSE(Math::IsNearZero(std::numeric_limits<long double>::quiet_NaN()));

	REQUIRE_FALSE(Math::IsNearZero(1e308));
	REQUIRE_FALSE(Math::IsNearZero(-1e308));
}

TEST_CASE("Math::IsNear", "[math_is_near]")
{
	REQUIRE(Math::IsNear(0.0, 0.0));
	REQUIRE(Math::IsNear(1.0, 1.0));
	REQUIRE(Math::IsNear(1024.0, 1024.0));
	REQUIRE(Math::IsNear(0.00001, 0.00001));
	REQUIRE(Math::IsNear(0.0, -0.0));

	REQUIRE(Math::IsNear(0.0f, 0.0f));
	REQUIRE(Math::IsNear(1.0f, 1.0f));
	REQUIRE(Math::IsNear(1024.0f, 1024.0f));
	REQUIRE(Math::IsNear(0.00001f, 0.00001f));

	REQUIRE_FALSE(Math::IsNear(0.0, 1.0));
	REQUIRE_FALSE(Math::IsNear(12.0, 12.0 + 0.001));
	REQUIRE_FALSE(Math::IsNear(1024.0, 1024.0 + 0.001));

	REQUIRE_FALSE(Math::IsNear(0.0f, 1.0f));
	REQUIRE_FALSE(Math::IsNear(12.0f, 12.0f + 0.001f));
	REQUIRE_FALSE(Math::IsNear(1024.0f, 1024.0f + 0.001f));

	REQUIRE_FALSE(Math::IsNear(0.0f, std::numeric_limits<float>::quiet_NaN()));
	REQUIRE_FALSE(Math::IsNear(1.0, std::numeric_limits<double>::quiet_NaN()));
	REQUIRE_FALSE(Math::IsNear(1024.0L, std::numeric_limits<long double>::quiet_NaN()));
}

TEST_CASE("Math::SafeDivide", "[math_safe_divide]")
{
	REQUIRE(Math::IsNear(Math::SafeDivide(9.0, 3.0), 3.0));
	REQUIRE(Math::IsNearZero(Math::SafeDivide(9.0, 0.0)));
}

TEST_CASE("Math::Dot2D", "[math_dot_2d]")
{
	REQUIRE(Math::IsNear(Math::Dot2D(1.0, 2.0, 3.0, 4.0), 11.0));
	REQUIRE(Math::IsNear(Math::Dot2D(0.0, 0.0, 5.0, 7.0), 0.0));
	REQUIRE(Math::IsNear(Math::Dot2D(-1.0, 4.0, 2.0, -3.0), -14.0));
}

TEST_CASE("Math::Dot3D", "[math_dot_3d]")
{
	REQUIRE(Math::IsNear(Math::Dot3D(1.0, 2.0, 3.0, 4.0, 5.0, 6.0), 32.0));
	REQUIRE(Math::IsNear(Math::Dot3D(0.0, 0.0, 0.0, 9.0, 8.0, 7.0), 0.0));
	REQUIRE(Math::IsNear(Math::Dot3D(-1.0, 2.0, -3.0, 4.0, -5.0, 6.0), -32.0));
}

TEST_CASE("Math::Dot4D", "[math_dot_4d]")
{
	REQUIRE(Math::IsNear(Math::Dot4D(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0), 70.0));
	REQUIRE(Math::IsNear(Math::Dot4D(0.0, 0.0, 0.0, 0.0, 3.0, 2.0, 1.0, 4.0), 0.0));
	REQUIRE(Math::IsNear(Math::Dot4D(-1.0, 2.0, -3.0, 4.0, -4.0, 3.0, -2.0, 1.0), 20.0));
}

TEST_CASE("Math::IsValidNumber", "[math_is_valid_number]")
{
	REQUIRE(Math::IsValidNumber(0.0));
	REQUIRE(Math::IsValidNumber(1024.0));
	REQUIRE(!Math::IsValidNumber(Math::Infinity));
}
