#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <vector>

#include "GCore/ScreenCoordinate.hpp"
#include "GCore/Input/InputDefines.hpp"

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

		constexpr GuiBounds operator*(const ScreenCoordinate& pixelSize) const
		{
			return GuiBounds
			{
				x * pixelSize.x,
				y * pixelSize.y,
				width * pixelSize.x,
				height * pixelSize.y,
			};
		}
	};

	using ClickCallback = std::function<bool(ButtonId, double, double)>;

	class GuiElement
	{
	public:
		GuiElement(GuiAnchor anchor, float w = 1.0f, float h = 1.0f, GuiElement* parent = nullptr);
		virtual ~GuiElement() = default;

		GuiBounds CalculateBounds() const;
		GuiBounds CalculatePixelBounds(const ScreenCoordinate& pixelSize) const;

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

		virtual bool OnClickDown(ButtonId button, double x, double y);
		virtual bool OnClickUp(ButtonId button, double x, double y);

		void SetOnClickDownCallback(ClickCallback func);
		void SetOnClickUpCallback(ClickCallback func);

		bool IsPointInBounds(float x, float y) const;

	protected:
		std::vector<std::unique_ptr<GuiElement>> subElements;
		GuiElement* parent;
		ClickCallback onClickDownCallback;
		ClickCallback onClickUpCallback;
		float width;
		float height;
		GuiAnchor anchor;
	};

	class GuiCanvas : public GuiElement
	{
	public:
		GuiCanvas() : GuiElement(GuiAnchor::MiddleCenter, 1.0f, 1.0f, nullptr){}
		virtual ~GuiCanvas() override = default;
	};
}
