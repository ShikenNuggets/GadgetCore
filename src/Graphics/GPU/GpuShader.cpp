#include "Graphics/GPU/GpuShader.hpp"

#include "Assert.hpp"
#include "Logger.hpp"

using namespace Gadget;

GpuShader::GpuShader(GpuDevice& gpuDevice, const RawShader& rawShader) : ownerDevice(gpuDevice), shader(nullptr)
{
	SDL_GPUShaderStage shaderStage;
	switch (rawShader.GetShaderType())
	{
		case ShaderType::Vertex:
			shaderStage = SDL_GPU_SHADERSTAGE_VERTEX;
			break;
		case ShaderType::Fragment:
			shaderStage = SDL_GPU_SHADERSTAGE_FRAGMENT;
			break;
		default:
			GADGET_ASSERT(false, "Tried to construct shader of invalid type {}", static_cast<uint8_t>(rawShader.GetShaderType())); // TODO - enum to string
			return;
	}

	SDL_GPUShaderFormat shaderFormat = SDL_GPU_SHADERFORMAT_SPIRV;
	if (rawShader.GetShaderFormat() != ShaderFormat::SPIRV)
	{
		// TODO - Support other formats
		GADGET_ASSERT(false, "Tried to construct shader of invalid format {}", static_cast<uint8_t>(rawShader.GetShaderFormat())); // TODO - enum to string
		return;
	}

	SDL_GPUShaderCreateInfo vertexInfo
	{
		.code_size = rawShader.GetShaderBytes().size(),
		.code = rawShader.GetShaderBytes().data(),
		.entrypoint = "main",
		.format = shaderFormat,
		.stage = shaderStage,
		.num_samplers = 0,
		.num_storage_textures = 0,
		.num_storage_buffers = 0,
		.num_uniform_buffers = rawShader.GetNumUniforms(),
	};

	shader = SDL_CreateGPUShader(ownerDevice.GetDevice(), &vertexInfo);
	if (shader == nullptr)
	{
		GADGET_LOG_ERROR("Failed to create vertex shader: {}", SDL_GetError());
		return;
	}
}

GpuShader::~GpuShader()
{
	SDL_ReleaseGPUShader(ownerDevice.GetDevice(), shader);
}
