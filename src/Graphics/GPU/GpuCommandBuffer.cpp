#include "GCore/Graphics/GPU/GpuCommandBuffer.hpp"

using namespace Gadget;

GpuCommandBuffer::GpuCommandBuffer(GpuDevice& gpuDevice, SDL_GPUTexture* depthTexture, const Color& clear) : ownerDevice(gpuDevice), commandBufferPtr(nullptr), clearColor(clear)
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

	SDL_GPUDepthStencilTargetInfo depthTargetInfo
	{
		.texture = depthTexture,
		.clear_depth = 1.0f,
		.load_op = SDL_GPU_LOADOP_CLEAR,
		.store_op = SDL_GPU_STOREOP_DONT_CARE,
		.stencil_load_op = SDL_GPU_LOADOP_DONT_CARE,
		.stencil_store_op = SDL_GPU_STOREOP_DONT_CARE
	};

	SDL_GPUDepthStencilTargetInfo* depthTargetInfoPtr = depthTexture ? &depthTargetInfo : nullptr;
	renderPassPtr = SDL_BeginGPURenderPass(commandBufferPtr, &colorTargetInfo, 1, depthTargetInfoPtr); // TODO - Error handling
}

GpuCommandBuffer::~GpuCommandBuffer()
{
	SDL_EndGPURenderPass(renderPassPtr);
	SDL_SubmitGPUCommandBuffer(commandBufferPtr);
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

void GpuCommandBuffer::Draw(GpuPipeline& pipeline, GpuVertexBuffer& vertexBuffer, GpuIndexBuffer& indexBuffer)
{
	SDL_BindGPUGraphicsPipeline(renderPassPtr, pipeline.GetPipeline());

	SDL_GPUBufferBinding vertexBufferBinding =
	{
		.buffer = vertexBuffer.GetBuffer(),
		.offset = 0
	};

	SDL_GPUBufferBinding indexBufferBinding =
	{
		.buffer = indexBuffer.GetBuffer(),
		.offset = 0
	};

	SDL_BindGPUVertexBuffers(renderPassPtr, 0, &vertexBufferBinding, 1);
	SDL_BindGPUIndexBuffer(renderPassPtr, &indexBufferBinding, SDL_GPU_INDEXELEMENTSIZE_32BIT);

	SDL_DrawGPUIndexedPrimitives(renderPassPtr, indexBuffer.GetIndexCount(), 1, 0, 0, 0);
}

void GpuCommandBuffer::BindVertexUniformInternal(GpuPipeline& pipeline, uint32_t slot, std::span<const uint8_t> data)
{
	SDL_BindGPUGraphicsPipeline(renderPassPtr, pipeline.GetPipeline());
	SDL_PushGPUVertexUniformData(commandBufferPtr, slot, data.data(), data.size_bytes());
}

void GpuCommandBuffer::BindFragmentUniformInternal(GpuPipeline& pipeline, uint32_t slot, std::span<const uint8_t> data)
{
	SDL_BindGPUGraphicsPipeline(renderPassPtr, pipeline.GetPipeline());
	SDL_PushGPUFragmentUniformData(commandBufferPtr, slot, data.data(), data.size_bytes());
}
