#pragma once

#include <string>

#include "MeshData.hpp"

namespace Gadget::MeshLoader
{
	ModelData LoadMeshFromFile(const std::string& filePath);
}
