#include "GCore/Graphics/GPU/GpuCommandBuffer.hpp"

using namespace Gadget;

GpuCommandBuffer::GpuCommandBuffer(GpuDevice& gpuDevice, const Color& clear) : ownerDevice(gpuDevice), commandBufferPtr(nullptr), clearColor(clear)
{
	commandBufferPtr = SDL_AcquireGPUCommandBuffer(ownerDevice.GetDevice()); // TODO - Error handling

	SDL_GPUTexture* swapchainTexture = nullptr;
	Uint32 width{};
	Uint32 height{};
	SDL_WaitAndAcquireGPUSwapchainTexture(commandBufferPtr, ownerDevice.GetOwnerWindow(), &swapchainTexture, &width, &height); // TODO - Error handling

	SDL_GPUColorTargetInfo colorTargetInfo
	{
		.texture = swapchainTexture,
		.clear_color = { clearColor.r, clearColor.g, clearColor.b, clearColor.a },
		.load_op = SDL_GPU_LOADOP_CLEAR,
		.store_op = SDL_GPU_STOREOP_STORE
	};

	renderPassPtr = SDL_BeginGPURenderPass(commandBufferPtr, &colorTargetInfo, 1, nullptr); // TODO - Error handling
}

void GpuCommandBuffer::Draw(GpuPipeline& pipeline, GpuVertexBuffer& buffer)
{
	SDL_BindGPUGraphicsPipeline(renderPassPtr, pipeline.GetPipeline());

	SDL_GPUBufferBinding bufferBindings[1]
	{{
		.buffer = buffer.GetBuffer(),
		.offset = 0
	}};

	SDL_BindGPUVertexBuffers(renderPassPtr, 0, bufferBindings, 1);

	SDL_DrawGPUPrimitives(renderPassPtr, buffer.GetVertexCount(), 1, 0, 0);
}

GpuCommandBuffer::~GpuCommandBuffer()
{
	SDL_EndGPURenderPass(renderPassPtr);
	SDL_SubmitGPUCommandBuffer(commandBufferPtr);
}
