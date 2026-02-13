#pragma once

#include <cstdint>
#include <vector>

#include "Vertex.hpp"

namespace Gadget
{
	struct MeshData
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};

	// A model contains one or more meshes
	struct ModelData
	{
		std::vector<MeshData> meshes;
	};
}
