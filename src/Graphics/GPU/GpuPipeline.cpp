#include "FileSystem.hpp"
#include "Logger.hpp"
#include "Graphics/GPU/GpuPipeline.hpp"

using namespace Gadget;

GpuPipeline::GpuPipeline(GpuDevice& owner, const RawShader& vertex, const RawShader& fragment) : ownerDevice(owner), pipelinePtr(nullptr)
{
	pipelinePtr = ownerDevice.CreateGraphicsPipeline(vertex, fragment);
}

GpuPipeline::GpuPipeline(GpuDevice& owner, std::string_view vertexFilePath, std::string_view fragmentFilePath) : ownerDevice(owner), pipelinePtr(nullptr)
{
	// Vertex Shader
	auto vertexCodeResult = Gadget::FileSystem::ReadFileRaw(vertexFilePath);
	if (!vertexCodeResult.has_value())
	{
		GADGET_LOG_ERROR("Failed to load vertex shader file!");
		throw -1; // TODO - Custom exception type
	}

	const auto& vertexCode = vertexCodeResult.value();
	auto rawVertexShader = Gadget::RawShader(vertexCode, Gadget::ShaderType::Vertex, Gadget::ShaderFormat::SPIRV);

	// Fragment Shader
	auto fragmentCodeResult = Gadget::FileSystem::ReadFileRaw(fragmentFilePath);
	if (!fragmentCodeResult.has_value())
	{
		GADGET_LOG_ERROR("Failed to load fragment shader file!");
		throw - 1; // TODO - Custom exception type
	}

	const auto& fragmentCode = fragmentCodeResult.value();
	auto rawFragmentShader = Gadget::RawShader(fragmentCode, Gadget::ShaderType::Fragment, Gadget::ShaderFormat::SPIRV);

	pipelinePtr = ownerDevice.CreateGraphicsPipeline(rawVertexShader, rawFragmentShader);
}

GpuPipeline::~GpuPipeline()
{
	SDL_ReleaseGPUGraphicsPipeline(ownerDevice.GetDevice(), pipelinePtr);
}
