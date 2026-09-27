#include "GCore/Graphics/GUI/GuiElement.hpp"

#include "GCore/Assert.hpp"

using namespace Gadget;

GuiElement::GuiElement(GuiAnchor anchor, float w, float h) : anchor(anchor), width(w), height(h)
{
	GADGET_ASSERT(width >= 0.0f && width <= 1.0f, "GuiElement width must be between 0 and 1");
	GADGET_ASSERT(height >= 0.0f && height <= 1.0f, "GuiElement height must be between 0 and 1");
}

void GuiElement::AddSubElement(GuiElement* element)
{
	subElements.push_back(std::unique_ptr<GuiElement>(element));
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
