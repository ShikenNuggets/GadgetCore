#pragma once

#include "Color.hpp"
#include "GCore/Math/Math.hpp"

namespace Gadget
{
	struct Vertex
	{
		explicit Vertex(const Gadget::Vector4& pos = Gadget::Vector4(0.0, 0.0, 0.0, 1.0), const Gadget::Color& color_ = Gadget::Color::Black()) : position(pos), color(color_){}

		Vector4 position;
		Color color;
	};
}
