#include "Graphics/MeshLoader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Assert.hpp"
#include "Logger.hpp"

using namespace Gadget;

static constexpr unsigned int gBaseFlags = 
	aiProcess_Triangulate
	| aiProcess_FlipUVs
	| aiProcess_JoinIdenticalVertices
	| aiProcess_LimitBoneWeights
	| aiProcess_ImproveCacheLocality
	| aiProcess_RemoveRedundantMaterials
	| aiProcess_FixInfacingNormals
	| aiProcess_FindInvalidData
	| aiProcess_GenUVCoords
	| aiProcess_OptimizeMeshes
	| aiProcess_OptimizeGraph
	| aiProcess_PopulateArmatureData;

#ifdef GADGET_BUILD_DEBUG
	static constexpr unsigned int gLoadFlags = gBaseFlags | aiProcess_ValidateDataStructure;
#else
	static constexpr unsigned int gLoadFlags = gBaseFlags;
#endif // GADGET_BUILD_DEBUG

static inline void ProcessMesh(const aiMesh* mesh, std::vector<MeshData>& outMeshes)
{
	GADGET_BASIC_ASSERT(mesh != nullptr);
	if (mesh == nullptr)
	{
		return;
	}

	std::vector<Vertex> verts;
	std::vector<unsigned int> indices;

	verts.reserve(mesh->mNumVertices);
	indices.reserve(static_cast<size_t>(mesh->mNumFaces) * 3);

	for (unsigned int j = 0; j < mesh->mNumVertices; j++)
	{
		const auto vertex = mesh->mVertices[j];
		const auto color = mesh->mColors[0][j];

		verts.emplace_back(
			Vector4(vertex.x, vertex.y, vertex.z, 1.0),
			Color(color.r, color.g, color.b, color.a)
		);
	}

	for (unsigned int j = 0; j < mesh->mNumFaces; j++)
	{
		for (unsigned int k = 0; k < mesh->mFaces[j].mNumIndices; k++)
		{
			indices.push_back(mesh->mFaces[j].mIndices[k]);
		}
	}

	outMeshes.emplace_back(MeshData{ .vertices = verts, .indices = indices });
}

static inline void ProcessNode(const aiNode* node, const aiScene* scene, std::vector<MeshData>& outMeshes)
{
	GADGET_BASIC_ASSERT(node != nullptr);
	GADGET_BASIC_ASSERT(scene != nullptr);

	outMeshes.reserve(outMeshes.size() + node->mNumMeshes);

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		auto meshIdx = node->mMeshes[i];
		ProcessMesh(scene->mMeshes[meshIdx], outMeshes);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene, outMeshes);
	}
}

ModelData MeshLoader::LoadMeshFromFile(const std::string& filePath)
{
	GADGET_BASIC_ASSERT(!filePath.empty());
	GADGET_BASIC_ASSERT(std::filesystem::exists(filePath));

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, gLoadFlags);
	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
	{
		GADGET_LOG_INFO("Assimp could not load model! Assimp Error: {}", importer.GetErrorString());
		return {};
	}

	ModelData model;
	ProcessNode(scene->mRootNode, scene, model.meshes);
	return model;
}
