#include <catch2/catch_all.hpp>

#include <GCore/ScreenCoordinate.hpp>

using namespace Gadget;

TEST_CASE("ScreenCoordinate::ScreenCoordinate", "[screen_coordinate_constructor]")
{
	const auto sc1 = ScreenCoordinate(1, 2);
	REQUIRE(sc1.x == 1);
	REQUIRE(sc1.y == 2);
}

TEST_CASE("ScreenCoordinate::operator==", "[screen_coordinate_operator_==]")
{
	const auto sc1 = ScreenCoordinate(1, 2);
	const auto sc2 = ScreenCoordinate(2, 3);
	REQUIRE(sc1 == sc1);
	REQUIRE(!(sc1 == sc2));
}
