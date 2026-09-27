#include "GCore/Graphics/GPU/GpuCommandBuffer.hpp"

#include "GCore/Logger.hpp"

using namespace Gadget;

GpuCommandBuffer::GpuCommandBuffer(GpuDevice& gpuDevice, SDL_GPUTexture* depthTexture, const Color& clear) : ownerDevice(gpuDevice), commandBufferPtr(nullptr), renderPassPtr(nullptr), clearColor(clear)
{
	commandBufferPtr = SDL_AcquireGPUCommandBuffer(ownerDevice.GetDevice());
	if (commandBufferPtr == nullptr)
	{
		GADGET_LOG_FATAL_ERROR("SDL_AcquireGPUCommandBuffer failed! SDL Error: ", SDL_GetError());
	}

	SDL_GPUTexture* swapchainTexture = nullptr;
	Uint32 width{};
	Uint32 height{};
	bool success = SDL_WaitAndAcquireGPUSwapchainTexture(commandBufferPtr, ownerDevice.GetOwnerWindow(), &swapchainTexture, &width, &height);
	if (!success)
	{
		GADGET_LOG_ERROR("SDL_WaitAndAcquireGPUSwapchainTexture failed! SDL Error: ", SDL_GetError());
		return;
	}

	if (swapchainTexture == nullptr)
	{
		return; // Null swapchain texture with no error usually means the window is minimized or something
	}

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
	renderPassPtr = SDL_BeginGPURenderPass(commandBufferPtr, &colorTargetInfo, 1, depthTargetInfoPtr);
	if (renderPassPtr == nullptr)
	{
		GADGET_LOG_ERROR("SDL_BeginGPURenderPass failed! SDL Error: ", SDL_GetError());
		return;
	}
}

GpuCommandBuffer::~GpuCommandBuffer()
{
	if (renderPassPtr == nullptr)
	{
		bool success = SDL_CancelGPUCommandBuffer(commandBufferPtr);
		if (!success)
		{
			GADGET_LOG_ERROR("Failed to cancel GPU command buffer! SDL Error: ", SDL_GetError());
		}

		return;
	}

	SDL_EndGPURenderPass(renderPassPtr);
	bool success = SDL_SubmitGPUCommandBuffer(commandBufferPtr);
	if (!success)
	{
		GADGET_LOG_ERROR("Failed to submit GPU command buffer! SDL Error: ", SDL_GetError());
	}
}

void GpuCommandBuffer::Draw(GpuPipeline& pipeline, GpuVertexBuffer& buffer)
{
	if (renderPassPtr == nullptr)
	{
		return;
	}

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
	if (renderPassPtr == nullptr)
	{
		return;
	}

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
	if (renderPassPtr == nullptr)
	{
		return;
	}

	SDL_BindGPUGraphicsPipeline(renderPassPtr, pipeline.GetPipeline());
	SDL_PushGPUVertexUniformData(commandBufferPtr, slot, data.data(), data.size_bytes());
}

void GpuCommandBuffer::BindFragmentUniformInternal(GpuPipeline& pipeline, uint32_t slot, std::span<const uint8_t> data)
{
	if (renderPassPtr == nullptr)
	{
		return;
	}

	SDL_BindGPUGraphicsPipeline(renderPassPtr, pipeline.GetPipeline());
	SDL_PushGPUFragmentUniformData(commandBufferPtr, slot, data.data(), data.size_bytes());
}
