#include "Graphics/GPU/GpuDevice.hpp"

#include "Assert.hpp"
#include "Logger.hpp"

#include "Graphics/Vertex.hpp"

using namespace Gadget;

GpuDevice::GpuDevice(SDL_Window* window) : ownerWindow(window), device(nullptr)
{
	GADGET_ASSERT(window != nullptr, "Tried to create GpuDevice with null window");

	bool isDebug = false;
	#ifdef GADGET_DEBUG
	isDebug = true;
	#endif // GADGET_DEBUG

	device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, isDebug, nullptr);
	if (device == nullptr)
	{
		GADGET_LOG_ERROR("Unable to create GPU device! SDL Error: {}", SDL_GetError());
		// TODO - Throw fatal error
	}
}

GpuDevice::~GpuDevice()
{
	SDL_DestroyGPUDevice(device);
}

SDL_GPUShader* GpuDevice::CreateShader(const RawShader& rawShader)
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
			return nullptr;
	}

	SDL_GPUShaderFormat shaderFormat = SDL_GPU_SHADERFORMAT_SPIRV;
	if (rawShader.GetShaderFormat() != ShaderFormat::SPIRV)
	{
		// TODO - Support other formats
		GADGET_ASSERT(false, "Tried to construct shader of invalid format {}", static_cast<uint8_t>(rawShader.GetShaderFormat())); // TODO - enum to string
		return nullptr;
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
		.num_uniform_buffers = 0,
	};

	SDL_GPUShader* shader = SDL_CreateGPUShader(device, &vertexInfo);
	if (shader == nullptr)
	{
		GADGET_LOG_ERROR("Failed to create vertex shader: {}", SDL_GetError());
		return nullptr;
	}

	return shader;
}

SDL_GPUBuffer* GpuDevice::CreateVertexBuffer(std::span<const uint8_t> data)
{
	GADGET_ASSERT(!data.empty(), "Tried to create vertex buffer with empty data");
	GADGET_ASSERT(device != nullptr, "Tried to create vertex buffer with invalid device");
	GADGET_ASSERT(data.size() <= std::numeric_limits<Uint32>::max(), "Tried to create vertex buffer with data size larger than Uint32 max");

	SDL_GPUBufferCreateInfo bufferInfo
	{
		.usage = SDL_GPU_BUFFERUSAGE_VERTEX,
		.size = static_cast<Uint32>(data.size())
	};
	SDL_GPUBuffer* vertexBuffer = SDL_CreateGPUBuffer(device, &bufferInfo);

	SDL_GPUTransferBufferCreateInfo transferInfo
	{
		.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
		.size = static_cast<Uint32>(data.size())
	};
	SDL_GPUTransferBuffer* transferBuffer = SDL_CreateGPUTransferBuffer(device, &transferInfo);

	auto* dataPtr = SDL_MapGPUTransferBuffer(device, transferBuffer, false);
	SDL_memcpy(dataPtr, data.data(), data.size());
	SDL_UnmapGPUTransferBuffer(device, transferBuffer);

	SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(device);
	SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(commandBuffer);

	SDL_GPUTransferBufferLocation location
	{
		.transfer_buffer = transferBuffer,
		.offset = 0,
	};

	SDL_GPUBufferRegion region
	{
		.buffer = vertexBuffer,
		.offset = 0,
		.size = static_cast<Uint32>(data.size())
	};

	SDL_UploadToGPUBuffer(copyPass, &location, &region, true);

	SDL_EndGPUCopyPass(copyPass);
	SDL_SubmitGPUCommandBuffer(commandBuffer);

	SDL_ReleaseGPUTransferBuffer(device, transferBuffer);

	return vertexBuffer;
}

SDL_GPUGraphicsPipeline* GpuDevice::CreateGraphicsPipeline(const RawShader& rawVertexShader, const RawShader& rawFragmentShader)
{
	auto* vertexShader = CreateShader(rawVertexShader);
	auto* fragmentShader = CreateShader(rawFragmentShader);

	SDL_GPUVertexBufferDescription vertexBufferDescriptions[1]
	{{
		.slot = 0,
		.pitch = sizeof(Gadget::Vertex),
		.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
		.instance_step_rate = 0
	}};

	SDL_GPUVertexAttribute vertexAttributes[2]{};
	vertexAttributes[0].buffer_slot = 0;
	vertexAttributes[0].location = 0;
	vertexAttributes[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
	vertexAttributes[0].offset = 0;

	vertexAttributes[1].buffer_slot = 0;
	vertexAttributes[1].location = 1;
	vertexAttributes[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4;
	vertexAttributes[1].offset = sizeof(Gadget::Vector4);

	SDL_GPUColorTargetDescription colorTargetDescriptions[1]
	{{
		.format = SDL_GetGPUSwapchainTextureFormat(device, ownerWindow)
	}};

	SDL_GPUGraphicsPipelineCreateInfo pipelineInfo
	{
		.vertex_shader = vertexShader,
		.fragment_shader = fragmentShader,
		.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
	};

	pipelineInfo.vertex_input_state.num_vertex_buffers = 1;
	pipelineInfo.vertex_input_state.vertex_buffer_descriptions = vertexBufferDescriptions;
	pipelineInfo.vertex_input_state.num_vertex_attributes = 2;
	pipelineInfo.vertex_input_state.vertex_attributes = vertexAttributes;
	pipelineInfo.target_info.num_color_targets = 1;
	pipelineInfo.target_info.color_target_descriptions = colorTargetDescriptions;

	SDL_GPUGraphicsPipeline* graphicsPipeline = SDL_CreateGPUGraphicsPipeline(device, &pipelineInfo);
	SDL_ReleaseGPUShader(device, fragmentShader);
	SDL_ReleaseGPUShader(device, vertexShader);

	return graphicsPipeline;
}
