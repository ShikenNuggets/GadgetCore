#include <catch2/catch_all.hpp>

#include "GCore/Math/Vector.hpp"

using namespace Gadget;

// --------------------------- //
// ---------- TVec2 ---------- //
// --------------------------- //
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

// --------------------------- //
// ---------- TVec3 ---------- //
// --------------------------- //
TEST_CASE("TVec3::TVec3", "[tvec3_constructor]")
{
	const TVec3<double> doubleVec3;
	REQUIRE(doubleVec3.x == 0.0);
	REQUIRE(doubleVec3.y == 0.0);
	REQUIRE(doubleVec3.z == 0.0);
}

// --------------------------- //
// ---------- TVec4 ---------- //
// --------------------------- //

TEST_CASE("TVec4::TVec4", "[tvec4_constructor]")
{
	const TVec4<double> doubleVec4;
	REQUIRE(doubleVec4.x == 0.0);
	REQUIRE(doubleVec4.y == 0.0);
	REQUIRE(doubleVec4.z == 0.0);
	REQUIRE(doubleVec4.w == 0.0);
}
