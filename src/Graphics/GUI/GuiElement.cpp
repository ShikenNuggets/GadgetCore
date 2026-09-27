#include "GCore/Graphics/GUI/GuiElement.hpp"

#include "GCore/Assert.hpp"

using namespace Gadget;

GuiElement::GuiElement(GuiAnchor anchor, float w, float h, GuiElement* parent) : anchor(anchor), width(w), height(h), parent(parent)
{
	GADGET_ASSERT(width >= 0.0f && width <= 1.0f, "GuiElement width must be between 0 and 1");
	GADGET_ASSERT(height >= 0.0f && height <= 1.0f, "GuiElement height must be between 0 and 1");
}

GuiBounds GuiElement::CalculateBounds(const ScreenCoordinate& pixelSize) const
{
	const auto parentBounds = parent ? parent->CalculateBounds(pixelSize) : GuiBounds{ 0.0f, 0.0f, static_cast<float>(pixelSize.x), static_cast<float>(pixelSize.y) };

	if (anchor == GuiAnchor::TopLeft)
	{
		return GuiBounds
		{
			parentBounds.x,
			parentBounds.y,
			parentBounds.width* width,
			parentBounds.height* height
		};
	}

	return parentBounds; // TODO - Implement other anchor types
}

GuiElement* GuiElement::AddSubElement(GuiElement* element)
{
	subElements.push_back(std::unique_ptr<GuiElement>(element));
	return element;
}

void GuiElement::SetWidth(float w)
{
	GADGET_ASSERT(w >= 0.0f && w <= 1.0f, "GuiElement width must be between 0 and 1");
	width = w;
}

void GuiElement::SetHeight(float h)
{
	GADGET_ASSERT(h >= 0.0f && h <= 1.0f, "GuiElement height must be between 0 and 1");
	height = h;
}
