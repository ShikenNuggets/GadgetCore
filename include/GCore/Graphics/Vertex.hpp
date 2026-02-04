#pragma once

#include "Color.hpp"
#include "GCore/Math/Math.hpp"

namespace Gadget
{
	struct Vertex
	{
		explicit Vertex(const Gadget::Vector3& pos = Gadget::Vector3::Zero(), const Gadget::Color& color_ = Gadget::Color::Black()) : position(pos), color(color_){}

		Vector3 position;
		Color color;
	};
}
