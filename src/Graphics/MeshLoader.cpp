#include "Graphics/MeshLoader.hpp"

#include <span>

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

	const auto sourceVerts = std::span(mesh->mVertices, mesh->mNumVertices);
	std::span<aiColor4D> sourceColorChannel;
	if (mesh->HasVertexColors(0))
	{
		sourceColorChannel = std::span(mesh->mColors[0], mesh->mNumVertices);
	}
	
	for (size_t i = 0; i < sourceVerts.size(); i++)
	{
		const auto& vertex = sourceVerts[i];
		auto color = Color::White();

		if (!sourceColorChannel.empty())
		{
			const auto assimpColor = sourceColorChannel[i];
			color = Color(assimpColor.r, assimpColor.g, assimpColor.b, assimpColor.a);
		}

		verts.emplace_back(Vector4(vertex.x, vertex.y, vertex.z, 1.0), color);
	}

	const auto sourceFaces = std::span(mesh->mFaces, mesh->mNumFaces);
	for (const auto& face : sourceFaces)
	{
		const auto sourceIndices = std::span(face.mIndices, face.mNumIndices);
		for (const auto& idx : sourceIndices)
		{
			indices.push_back(idx);
		}
	}

	outMeshes.emplace_back(MeshData{ .vertices = verts, .indices = indices });
}

static inline void ProcessNode(const aiNode* node, const aiScene* scene, std::vector<MeshData>& outMeshes)
{
	GADGET_BASIC_ASSERT(node != nullptr);
	GADGET_BASIC_ASSERT(scene != nullptr);

	outMeshes.reserve(outMeshes.size() + node->mNumMeshes);

	const auto sourceMeshIndices = std::span(node->mMeshes, node->mNumMeshes);
	const auto sourceMeshes = std::span(scene->mMeshes, scene->mNumMeshes);
	for (const auto& meshIdx : sourceMeshIndices)
	{
		GADGET_BASIC_ASSERT(meshIdx < sourceMeshes.size());
		ProcessMesh(sourceMeshes[meshIdx], outMeshes);
	}

	const auto sourceChildren = std::span(node->mChildren, node->mNumChildren);
	for (const auto& child : sourceChildren)
	{
		GADGET_BASIC_ASSERT(child != nullptr);
		ProcessNode(child, scene, outMeshes);
	}
}

ModelData MeshLoader::LoadMeshFromFile(const std::string& filePath)
{
	GADGET_BASIC_ASSERT(!filePath.empty());
	GADGET_BASIC_ASSERT(std::filesystem::exists(filePath));

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filePath, gLoadFlags);
	if (scene == nullptr || static_cast<bool>(scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || scene->mRootNode == nullptr)
	{
		GADGET_LOG_INFO("Assimp could not load model! Assimp Error: {}", importer.GetErrorString());
		return {};
	}

	ModelData model;
	ProcessNode(scene->mRootNode, scene, model.meshes);
	return model;
}
