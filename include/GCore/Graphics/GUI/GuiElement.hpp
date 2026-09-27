#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include <GCore/ScreenCoordinate.hpp>

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

	struct GuiBounds
	{
		float x = 0.0f;
		float y = 0.0f;
		float width = -1.0f;
		float height = -1.0f;
	};

	class GuiElement
	{
	public:
		GuiElement(GuiAnchor anchor, float w = 1.0f, float h = 1.0f, GuiElement* parent = nullptr);
		~GuiElement() = default;

		GuiBounds CalculateBounds(const ScreenCoordinate& pixelSize) const;

		GuiElement* AddSubElement(GuiElement* element);
		const std::vector<std::unique_ptr<GuiElement>>& GetSubElements() const{ return subElements; }
		std::vector<std::unique_ptr<GuiElement>>& GetSubElements(){ return subElements; }

		GuiAnchor GetAnchor() const{ return anchor; }
		float GetWidth() const{ return width; }
		float GetHeight() const{ return height; }
		GuiElement* GetParent() const{ return parent; }

		void SetAnchor(GuiAnchor a){ anchor = a; }
		void SetWidth(float w);
		void SetHeight(float h);
		void SetParent(GuiElement* p){ parent = p; }

	protected:
		std::vector<std::unique_ptr<GuiElement>> subElements;
		GuiElement* parent;
		float width;
		float height;
		GuiAnchor anchor;
	};
}
