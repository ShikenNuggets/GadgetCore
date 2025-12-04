#include <catch2/catch_all.hpp>

#include <GCore/Math/Quaternion.hpp>

using namespace Gadget;

TEST_CASE("TQuat::TQuat", "[tquat_constructor]")
{
	const TQuat<double> doubleQuat;
	REQUIRE(doubleQuat.x == 0.0);
	REQUIRE(doubleQuat.y == 0.0);
	REQUIRE(doubleQuat.z == 0.0);
	REQUIRE(doubleQuat.w == 0.0);
}
