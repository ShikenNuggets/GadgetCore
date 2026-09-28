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

	GuiBounds finalBounds;

	// X alignment
	if (anchor == GuiAnchor::TopLeft || anchor == GuiAnchor::MiddleLeft || anchor == GuiAnchor::BottomLeft)
	{
		finalBounds.x = parentBounds.x;
	}
	else if(anchor == GuiAnchor::TopCenter || anchor == GuiAnchor::MiddleCenter || anchor == GuiAnchor::BottomCenter)
	{
		finalBounds.x = parentBounds.x + (parentBounds.width / 2.0f) - ((parentBounds.width * width) / 2.0f);
	}
	else if(anchor == GuiAnchor::TopRight || anchor == GuiAnchor::MiddleRight || anchor == GuiAnchor::BottomRight)
	{
		finalBounds.x = parentBounds.x + parentBounds.width - (parentBounds.width * width);
	}

	// Y alignment
	if (anchor == GuiAnchor::TopLeft || anchor == GuiAnchor::TopCenter || anchor == GuiAnchor::TopRight)
	{
		finalBounds.y = parentBounds.y;
	}
	else if(anchor == GuiAnchor::MiddleLeft || anchor == GuiAnchor::MiddleCenter || anchor == GuiAnchor::MiddleRight)
	{
		finalBounds.y = parentBounds.y + (parentBounds.height / 2.0f) - ((parentBounds.height * height) / 2.0f);
	}
	else if(anchor == GuiAnchor::BottomLeft || anchor == GuiAnchor::BottomCenter || anchor == GuiAnchor::BottomRight)
	{
		finalBounds.y = parentBounds.y + parentBounds.height - (parentBounds.height * height);
	}

	finalBounds.width = parentBounds.width * width;
	finalBounds.height = parentBounds.height * height;
	return finalBounds;
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
