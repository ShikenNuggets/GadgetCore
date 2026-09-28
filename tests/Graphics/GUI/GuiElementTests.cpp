#include <catch2/catch_all.hpp>

#include <GCore/Graphics/GUI/GuiElement.hpp>

using namespace Gadget;
using Catch::Approx;

TEST_CASE("GuiElement::GuiElement", "[gui_element_constructor]")
{
	const auto defaultElement = GuiElement(GuiAnchor::MiddleCenter);
	REQUIRE(defaultElement.GetAnchor() == GuiAnchor::MiddleCenter);
	REQUIRE(defaultElement.GetWidth() == 1.0f);
	REQUIRE(defaultElement.GetHeight() == 1.0f);
	REQUIRE(defaultElement.GetSubElements().empty());

	const auto element = GuiElement(GuiAnchor::TopLeft, 0.5f, 0.8f);
	REQUIRE(element.GetAnchor() == GuiAnchor::TopLeft);
	REQUIRE(element.GetWidth() == Approx(0.5f));
	REQUIRE(element.GetHeight() == Approx(0.8f));
	REQUIRE(element.GetSubElements().empty());
}

TEST_CASE("GuiElement::CalculateBounds", "[gui_element_calculate_bounds]")
{
	const auto pixelSize = ScreenCoordinate(1000, 1000);
	const auto topLeftElement = GuiElement(GuiAnchor::TopLeft, 0.5f, 0.5f);
	const auto topLeftBounds = topLeftElement.CalculateBounds(pixelSize);
	REQUIRE(topLeftBounds.x == Approx(0.0f));
	REQUIRE(topLeftBounds.y == Approx(0.0f));
	REQUIRE(topLeftBounds.width == Approx(500.0f));
	REQUIRE(topLeftBounds.height == Approx(500.0f));

	const auto middleCenterElement = GuiElement(GuiAnchor::MiddleCenter, 0.5f, 0.5f);
	const auto middleCenterBounds = middleCenterElement.CalculateBounds(pixelSize);
	REQUIRE(middleCenterBounds.x == Approx(250.0f));
	REQUIRE(middleCenterBounds.y == Approx(250.0f));
	REQUIRE(middleCenterBounds.width == Approx(500.0f));
	REQUIRE(middleCenterBounds.height == Approx(500.0f));
}

TEST_CASE("GuiElement::AddSubElement", "[gui_element_add_sub_element]")
{
	auto element = GuiElement(GuiAnchor::TopLeft, 0.5f, 0.5f);
	REQUIRE(element.GetSubElements().empty());

	auto* subElement = new GuiElement(GuiAnchor::TopCenter, 0.3f, 0.3f);
	auto* addedElement = element.AddSubElement(subElement);
	REQUIRE(element.GetSubElements().size() == 1);
	REQUIRE(element.GetSubElements()[0].get() == subElement);
	REQUIRE(addedElement == subElement);
}

TEST_CASE("GuiElement::SetAnchor", "[gui_element_set_anchor]")
{
	auto element = GuiElement(GuiAnchor::MiddleCenter, 0.5f, 0.5f);
	REQUIRE(element.GetAnchor() == GuiAnchor::MiddleCenter);
	element.SetAnchor(GuiAnchor::BottomRight);
	REQUIRE(element.GetAnchor() == GuiAnchor::BottomRight);
}

TEST_CASE("GuiElement::SetWidth", "[gui_element_set_width]")
{
	auto element = GuiElement(GuiAnchor::MiddleCenter, 0.5f, 0.5f);
	REQUIRE(element.GetWidth() == Approx(0.5f));
	element.SetWidth(0.8f);
	REQUIRE(element.GetWidth() == Approx(0.8f));
}

TEST_CASE("GuiElement::SetHeight", "[gui_element_set_height]")
{
	auto element = GuiElement(GuiAnchor::MiddleCenter, 0.5f, 0.5f);
	REQUIRE(element.GetHeight() == Approx(0.5f));
	element.SetHeight(0.8f);
	REQUIRE(element.GetHeight() == Approx(0.8f));
}

TEST_CASE("GuiElement::SetParent", "[gui_element_set_parent]")
{
	auto parentElement = GuiElement(GuiAnchor::MiddleCenter, 0.5f, 0.5f);
	auto childElement = GuiElement(GuiAnchor::TopLeft, 0.3f, 0.3f);
	REQUIRE(childElement.GetParent() == nullptr);
	childElement.SetParent(&parentElement);
	REQUIRE(childElement.GetParent() == &parentElement);
}
