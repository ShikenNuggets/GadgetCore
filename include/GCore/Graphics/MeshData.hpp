#pragma once

#include <cstdint>
#include <vector>

#include "Vertex.hpp"

namespace Gadget
{
	class MeshData
	{
	public:
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};
}
