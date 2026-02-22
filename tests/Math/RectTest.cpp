#include <catch2/catch_all.hpp>

#include "GCore/Math/Rect.hpp"

using namespace Gadget;
using Catch::Approx;

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
	REQUIRE(!doubleRect.IsValid());

	doubleRect.AddBounds(-2.0, -4.0);
	doubleRect.AddBounds(6.0, 8.0);
	REQUIRE(doubleRect.min.x == -2.0);
	REQUIRE(doubleRect.min.y == -4.0);
	REQUIRE(doubleRect.max.x == 6.0);
	REQUIRE(doubleRect.max.y == 8.0);
}

TEST_CASE("TRect::GetSize", "[trect_get_size]")
{
	const auto doubleRect = TRect<double>(1.0, 2.0, 3.0, 4.0);
	REQUIRE(doubleRect.GetSize().x == Approx(2.0));
	REQUIRE(doubleRect.GetSize().y == Approx(2.0));

	const auto negRect = TRect<double>(5.0, 4.0, 2.0, 0.0);
	REQUIRE(negRect.GetSize().x == Approx(-3.0));
	REQUIRE(negRect.GetSize().y == Approx(-4.0));
}

TEST_CASE("TRect::GetWidth", "[trect_get_width]")
{
	const auto doubleRect = TRect<double>(1.0, 2.0, 3.0, 4.0);
	REQUIRE(doubleRect.GetSize().x == doubleRect.GetWidth());
}

TEST_CASE("TRect::GetHeight", "[trect_get_height]")
{
	const auto doubleRect = TRect<double>(1.0, 2.0, 3.0, 4.0);
	REQUIRE(doubleRect.GetSize().y == doubleRect.GetHeight());
}

TEST_CASE("TRect::IsValid", "[trect_is_valid]")
{
	const auto validVec = TVec2<double>(1.0, 2.0);
	const auto invalidVec = TVec2<double>(Math::TInfinity<double>, 0.0);

	TRect<double> doubleRect;
	REQUIRE(!doubleRect.IsValid());

	doubleRect.min = validVec;
	doubleRect.max = validVec;
	REQUIRE(doubleRect.IsValid());

	// Just min invalid
	doubleRect.min = invalidVec;
	REQUIRE(!doubleRect.IsValid());

	// Both invalid
	doubleRect.max = invalidVec;
	REQUIRE(!doubleRect.IsValid());

	// Just max invalid
	doubleRect.min = validVec;
	REQUIRE(!doubleRect.IsValid());
}
