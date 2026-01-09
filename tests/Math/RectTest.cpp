#include <catch2/catch_all.hpp>

#include "GCore/Math/Rect.hpp"

using namespace Gadget;

TEST_CASE("TRect::TRect", "[trect_constructor]")
{
	const auto doubleRect = TRect<double>(1.0, 2.0, 3.0, 4.0);
	REQUIRE(doubleRect.min.x == 1.0);
	REQUIRE(doubleRect.min.y == 2.0);
	REQUIRE(doubleRect.max.x == 3.0);
	REQUIRE(doubleRect.max.y == 4.0);
}

TEST_CASE("TRect::AddBounds", "[trect_add_bounds]")
{
	TRect<double> doubleRect;
	REQUIRE(!doubleRect.min.IsValid());
	REQUIRE(!doubleRect.max.IsValid());

	doubleRect.AddBounds(-2.0, -4.0);
	doubleRect.AddBounds(6.0, 8.0);
	REQUIRE(doubleRect.min.x == -2.0);
	REQUIRE(doubleRect.min.y == -4.0);
	REQUIRE(doubleRect.max.x == 6.0);
	REQUIRE(doubleRect.max.y == 8.0);
}
