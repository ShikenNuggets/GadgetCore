#pragma once

#include <cstdint>
#include <memory>
#include <vector>

namespace Gadget
{
	enum class GuiAnchor : uint8_t
	{
		TopLeft,
		TopCenter,
		TopRight,
		MiddleLeft,
		MiddleCenter,
		MiddleRight,
		BottomLeft,
		BottomCenter,
		BottomRight
	};

	class GuiElement
	{
	public:
		GuiElement(GuiAnchor anchor, float w = 1.0f, float h = 1.0f);
		~GuiElement() = default;

		void AddSubElement(GuiElement* element);
		const std::vector<std::unique_ptr<GuiElement>>& GetSubElements() const{ return subElements; }
		std::vector<std::unique_ptr<GuiElement>>& GetSubElements(){ return subElements; }

		GuiAnchor GetAnchor() const{ return anchor; }
		float GetWidth() const{ return width; }
		float GetHeight() const{ return height; }

		void SetAnchor(GuiAnchor a){ anchor = a; }
		void SetWidth(float w);
		void SetHeight(float h);

	protected:
		std::vector<std::unique_ptr<GuiElement>> subElements;
		float width;
		float height;
		GuiAnchor anchor;
	};
}
