#include <catch2/catch_all.hpp>

#include <GCore/Graphics/Color.hpp>

using namespace Gadget;
using Catch::Approx;

TEST_CASE("Color::Color", "[color_constructor]")
{
	const auto color = Color(0.3f, 0.6f, 0.9f, 1.2f);
	REQUIRE(color.r == 0.3f);
	REQUIRE(color.g == 0.6f);
	REQUIRE(color.b == 0.9f);
	REQUIRE(color.a == 1.0f);
}

TEST_CASE("Color::ToLinear", "[color_to_linear]")
{
	const auto color = Color(0.3f, 0.6f, 0.9f, 1.0f);
	const auto linear = color.ToLinear();
	const auto srgb = linear.ToSRGB();

	REQUIRE(srgb.r == Approx(color.r));
	REQUIRE(srgb.g == Approx(color.g));
	REQUIRE(srgb.b == Approx(color.b));
	REQUIRE(srgb.a == Approx(color.a));

	// TODO - Validate the actual math here
}

TEST_CASE("Color::ToSRGB", "[color_to_srgb]")
{
	const auto color = Color(0.3f, 0.6f, 0.9f, 1.0f);
	const auto srgb = color.ToSRGB();
	const auto linear = srgb.ToLinear();

	REQUIRE(linear.r == Approx(color.r));
	REQUIRE(linear.g == Approx(color.g));
	REQUIRE(linear.b == Approx(color.b));
	REQUIRE(linear.a == Approx(color.a));

	// TODO - Validate the actual math here
}
