#include <catch2/catch_all.hpp>

#include <GCore/Graphics/MeshData.hpp>

using namespace Gadget;

TEST_CASE("MeshData::MeshData", "[mesh_data_constructor]")
{
	const auto meshData = MeshData();
	REQUIRE(meshData.vertices.empty());
	REQUIRE(meshData.indices.empty());
}
