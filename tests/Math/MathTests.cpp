#include <iostream>

#include <catch2/catch_all.hpp>

#include "GCore/Math/Math.hpp"

using namespace Gadget;

TEST_CASE("Math::IsValidNumber", "[math_is_valid_number]")
{
	REQUIRE(Math::IsValidNumber(0.0));
	REQUIRE(Math::IsValidNumber(1024.0));
	REQUIRE(!Math::IsValidNumber(Math::Infinity));
}

TEST_CASE("Math::DegreesToRadians", "[math_degrees_to_radians]")
{
	REQUIRE(Math::IsNear(Math::DegreesToRadians(0.0), 0.0));
	REQUIRE(Math::IsNear(Math::DegreesToRadians(90.0), std::numbers::pi_v<double> / 2.0));
	REQUIRE(Math::IsNear(Math::DegreesToRadians(180.0), std::numbers::pi_v<double>));
	REQUIRE(Math::IsNear(Math::DegreesToRadians(360.0), std::numbers::pi_v<double> * 2.0));
}

TEST_CASE("Math::RadiansToDegrees", "[math_radians_to_degrees]")
{
	REQUIRE(Math::IsNear(Math::RadiansToDegrees(0.0), 0.0));
	REQUIRE(Math::IsNear(Math::RadiansToDegrees(std::numbers::pi_v<double> / 2.0), 90.0));
	REQUIRE(Math::IsNear(Math::RadiansToDegrees(std::numbers::pi_v<double>), 180.0));
	REQUIRE(Math::IsNear(Math::RadiansToDegrees(std::numbers::pi_v<double> * 2.0), 360.0));
}

TEST_CASE("Math::Sqrt", "[math_sqrt]")
{
	REQUIRE(Math::IsNear(Math::Sqrt(16.0), 4.0));
	REQUIRE(Math::IsNear(Math::Sqrt(0.0), 0.0));
	REQUIRE(Math::IsNear(Math::Sqrt(1.0), 1.0));
	REQUIRE(!Math::IsValidNumber(Math::Sqrt(-1.0)));
}

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

TEST_CASE("Math::Abs", "[math_abs]")
{
	REQUIRE(Math::Abs(-1) == 1);
	REQUIRE(Math::Abs(1) == 1);
	REQUIRE(Math::Abs(static_cast<uint8_t>(254u)) == 254);
	REQUIRE(Math::Abs(Math::Infinity) == Math::Infinity);
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

TEST_CASE("Math::Clamp", "[math_clamp]")
{
	REQUIRE(Math::Clamp(0, 9, 10) == 9);
	REQUIRE(Math::Clamp(0, 9, -10) == 0);
	REQUIRE(Math::IsNear(Math::Clamp(0.0, 1.0, 0.5), 0.5));
}

TEST_CASE("Math::SinR", "[math_sin_r]")
{
	REQUIRE(Math::IsNear(Math::SinR(0.0), 0.0));
	REQUIRE(Math::IsNear(Math::SinR(std::numbers::pi_v<double> / 6.0), 0.5));
	REQUIRE(Math::IsNear(Math::SinR(std::numbers::pi_v<double> / 4.0), std::sin(std::numbers::pi_v<double> / 4.0)));
	REQUIRE(Math::IsNear(Math::SinR(std::numbers::pi_v<double> / 2.0), 1.0));
	REQUIRE(Math::IsNear(Math::SinR(std::numbers::pi_v<double>), 0.0));
	REQUIRE(Math::IsNear(Math::SinR(3 * std::numbers::pi_v<double> / 2.0), -1.0));
	REQUIRE(Math::IsNear(Math::SinR(2 * std::numbers::pi_v<double>), 0.0));
}

TEST_CASE("Math::CosR", "[math_cos_r]")
{
	REQUIRE(Math::IsNear(Math::CosR(0.0), 1.0));
	REQUIRE(Math::IsNear(Math::CosR(std::numbers::pi_v<double> / 6.0), std::cos(std::numbers::pi_v<double> / 6.0)));
	REQUIRE(Math::IsNear(Math::CosR(std::numbers::pi_v<double> / 4.0), std::cos(std::numbers::pi_v<double> / 4.0)));
	REQUIRE(Math::IsNear(Math::CosR(std::numbers::pi_v<double> / 2.0), 0.0));
	REQUIRE(Math::IsNear(Math::CosR(std::numbers::pi_v<double>), -1.0));
	REQUIRE(Math::IsNear(Math::CosR(3 * std::numbers::pi_v<double> / 2.0), 0.0));
	REQUIRE(Math::IsNear(Math::CosR(2 * std::numbers::pi_v<double>), 1.0));
}

TEST_CASE("Math::TanR", "[math_tan_r]")
{
	REQUIRE(Math::IsNear(Math::TanR(0.0), 0.0));
	REQUIRE(Math::IsNear(Math::TanR(std::numbers::pi_v<double> / 4.0), 1.0));
	REQUIRE(Math::IsNear(Math::TanR(std::numbers::pi_v<double> / 6.0), std::tan(std::numbers::pi_v<double> / 6.0)));
	REQUIRE(Math::IsNear(Math::TanR(std::numbers::pi_v<double> / 2.0), std::tan(std::numbers::pi_v<double> / 2.0)));
	REQUIRE(Math::IsNear(Math::TanR(3.0 * std::numbers::pi_v<double> / 4.0), -1.0));
	REQUIRE(Math::IsNear(Math::TanR(std::numbers::pi_v<double>), 0.0));
	REQUIRE(Math::IsNear(Math::TanR(3.0 * std::numbers::pi_v<double> / 2.0), std::tan(3.0 * std::numbers::pi_v<double> / 2.0)));
}

TEST_CASE("Math::Sin", "[math_sin]")
{
	REQUIRE(Math::IsNear(Math::Sin(0.0), 0.0));
	REQUIRE(Math::IsNear(Math::Sin(30.0), 0.5));
	REQUIRE(Math::IsNear(Math::Sin(45.0), std::sin(std::numbers::pi_v<double> / 4.0)));
	REQUIRE(Math::IsNear(Math::Sin(90.0), 1.0));
	REQUIRE(Math::IsNear(Math::Sin(180.0), 0.0));
	REQUIRE(Math::IsNear(Math::Sin(270.0), -1.0));
	REQUIRE(Math::IsNear(Math::Sin(360.0), 0.0));
}

TEST_CASE("Math::Cos", "[math_cos]")
{
	REQUIRE(Math::IsNear(Math::Cos(0.0), 1.0));
	REQUIRE(Math::IsNear(Math::Cos(30.0), std::cos(std::numbers::pi_v<double> / 6.0)));
	REQUIRE(Math::IsNear(Math::Cos(45.0), std::cos(std::numbers::pi_v<double> / 4.0)));
	REQUIRE(Math::IsNear(Math::Cos(90.0), 0.0));
	REQUIRE(Math::IsNear(Math::Cos(180.0), -1.0));
	REQUIRE(Math::IsNear(Math::Cos(270.0), 0.0));
	REQUIRE(Math::IsNear(Math::Cos(360.0), 1.0));
}

TEST_CASE("Math::Tan", "[math_tan]")
{
	REQUIRE(Math::IsNear(Math::Tan(0.0), 0.0));
	REQUIRE(Math::IsNear(Math::Tan(45.0), 1.0));
	REQUIRE(Math::IsNear(Math::Tan(90.0), std::tan(std::numbers::pi_v<double> / 2.0)));
	REQUIRE(Math::IsNear(Math::Tan(180.0), 0.0));
	REQUIRE(Math::IsNear(Math::Tan(270.0), std::tan(3 * std::numbers::pi_v<double> / 2.0)));
}

TEST_CASE("Math::Asin", "[math_asin]")
{
	REQUIRE(Math::IsNear(Math::Asin(0.0), 0.0));
	REQUIRE(Math::IsNear(Math::Asin(0.5), 30.0));
	REQUIRE(Math::IsNear(Math::Asin(1.0), 90.0));
	REQUIRE(Math::IsNear(Math::Asin(-1.0), -90.0));
}

TEST_CASE("Math::Acos", "[math_acos]")
{
	REQUIRE(Math::IsNear(Math::Acos(1.0), 0.0));
	REQUIRE(Math::IsNear(Math::Acos(0.5), 60.0));
	REQUIRE(Math::IsNear(Math::Acos(0.0), 90.0));
	REQUIRE(Math::IsNear(Math::Acos(-1.0), 180.0));
}

TEST_CASE("Math::Atan", "[math_atan]")
{
	REQUIRE(Math::IsNear(Math::Atan(0.0), 0.0));
	REQUIRE(Math::IsNear(Math::Atan(1.0), 45.0));
	REQUIRE(Math::IsNear(Math::Atan(-1.0), -45.0));
	REQUIRE(Math::IsNear(Math::Atan(10.0), 84.289406));
}

TEST_CASE("Math::Atan2", "[math_atan2]")
{
	REQUIRE(Math::IsNear(Math::Atan2(0.0, 0.0), 0.0));
	REQUIRE(Math::IsNear(Math::Atan2(1.0, 1.0), 45.0));
	REQUIRE(Math::IsNear(Math::Atan2(-1.0, -1.0), -135.0));
	REQUIRE(Math::IsNear(Math::Atan2(1.0, 0.0), 90.0));
	REQUIRE(Math::IsNear(Math::Atan2(0.0, 1.0), 0.0));
}

TEST_CASE("Math::IsPrime", "[math_is_prime]")
{
	REQUIRE(!Math::IsPrime(0));
	REQUIRE(!Math::IsPrime(1));
	REQUIRE(Math::IsPrime(2));
	REQUIRE(Math::IsPrime(3));
	REQUIRE(!Math::IsPrime(4));
	REQUIRE(Math::IsPrime(5));
	REQUIRE(!Math::IsPrime(6));
	REQUIRE(Math::IsPrime(7));

	//REQUIRE(Math::IsPrime(Math::LargestPrime)); // This is pretty slow
}

TEST_CASE("Math::NextPrime", "[math_next_prime]")
{
	REQUIRE(Math::NextPrime(0) == 2);
	REQUIRE(Math::NextPrime(1) == 2);
	REQUIRE(Math::NextPrime(2) == 3);
	REQUIRE(Math::NextPrime(3) == 5);
	REQUIRE(Math::NextPrime(4) == 5);
	REQUIRE(Math::NextPrime(5) == 7);
	REQUIRE(Math::NextPrime(6) == 7);
	REQUIRE(Math::NextPrime(7) == 11);
}

TEST_CASE("Math::IsInteger", "[math_is_integer]")
{
	REQUIRE(Math::IsInteger(1.0));
	REQUIRE(Math::IsInteger(2.0));
	REQUIRE(!Math::IsInteger(2.01));
	REQUIRE(Math::IsInteger(-3.0));
	REQUIRE(!Math::IsInteger(-3.9));
}

TEST_CASE("Math::RemapRange", "[math_remap_range]")
{
	REQUIRE(Math::IsNear(Math::RemapRange(5.0, 0.0, 10.0, 0.0, 100.0), 50.0));
	REQUIRE(Math::IsNear(Math::RemapRange(0.0, 0.0, 10.0, 0.0, 100.0), 0.0));
	REQUIRE(Math::IsNear(Math::RemapRange(10.0, 0.0, 10.0, 0.0, 100.0), 100.0));
	REQUIRE(Math::IsNear(Math::RemapRange(5.0, 0.0, 10.0, 0.0, 1.0), 0.5));
	REQUIRE(Math::IsNear(Math::RemapRange(2.5, 0.0, 5.0, -100.0, 100.0), 0.0));
	REQUIRE(Math::IsNear(Math::RemapRange(-5.0, -10.0, 0.0, 0.0, 100.0), 50.0));
	REQUIRE(Math::IsNear(Math::RemapRange(5.0, 0.0, 5.0, 0.0, 2.0), 2.0));

	REQUIRE(Math::IsNear(Math::RemapRange(5.0, 5.0, 5.0, 0.0, 10.0), 0.0));
	REQUIRE(Math::IsNear(Math::RemapRange(5.0, 0.0, 0.0, 0.0, 10.0), 0.0));

	REQUIRE(Math::IsNear(Math::RemapRange(5.0, 0.0, 10.0, 0.0, 0.0), 0.0));
	REQUIRE(Math::IsNear(Math::RemapRange(5.0, 0.0, 10.0, 10.0, 10.0), 10.0));
}
