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
