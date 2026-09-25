#pragma once

#include "Color.hpp"
#include "GCore/Math/Math.hpp"

namespace Gadget
{
	struct Vertex
	{
		explicit constexpr Vertex(const Gadget::Vector3& pos = Gadget::Vector3(0.0, 0.0, 0.0), const Gadget::Vector3& normal_ = Gadget::Vector3(0.0, 0.0, 1.0), const Gadget::Vector2& texCoords_ = Gadget::Vector2(0.0, 0.0)) : position(pos), normal(normal_), texCoords(texCoords_){}

		Vector3 position;
		Vector3 normal;
		Vector2 texCoords;
	};
}
