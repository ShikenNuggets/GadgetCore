#include "Graphics/GPU/GpuDevice.hpp"

#include "Assert.hpp"
#include "Logger.hpp"

using namespace Gadget;

GpuDevice::GpuDevice()
{
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
