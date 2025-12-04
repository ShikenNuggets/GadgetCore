#include <catch2/catch_all.hpp>

#include <GCore/Math/Quaternion.hpp>

using namespace Gadget;

TEST_CASE("TQuat::TQuat", "[tquat_constructor]")
{
	const auto defaultInit = TQuat<double>();
	REQUIRE(defaultInit.w == 1.0);
	REQUIRE(defaultInit.x == 0.0);
	REQUIRE(defaultInit.y == 0.0);
	REQUIRE(defaultInit.z == 0.0);

	const auto customInit = TQuat<double>(1.0, 2.0, 3.0, 4.0);
	REQUIRE(customInit.w == 1.0);
	REQUIRE(customInit.x == 2.0);
	REQUIRE(customInit.y == 3.0);
	REQUIRE(customInit.z == 4.0);
}

TEST_CASE("TQuat::Identity", "[tquat_identity]")
{
	const TQuat<double> doubleQuat = TQuat<double>::Identity();
	REQUIRE(doubleQuat.w == 1.0);
	REQUIRE(doubleQuat.x == 0.0);
	REQUIRE(doubleQuat.y == 0.0);
	REQUIRE(doubleQuat.z == 0.0);
}
