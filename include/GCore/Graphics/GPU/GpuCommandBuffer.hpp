#pragma once

#include <SDL3/SDL.h>

#include "GpuBuffer.hpp"
#include "GpuDevice.hpp"
#include "GpuPipeline.hpp"
#include "GCore/Graphics/Color.hpp"

namespace Gadget
{
	class GpuCommandBuffer
	{
	public:
		GpuCommandBuffer(GpuDevice& gpuDevice, const Color& clear = Color::Black());
		~GpuCommandBuffer();

		Color GetClearColor() const{ return clearColor; }
		void SetClearColor(const Color& newClearColor){ clearColor = newClearColor; }

		void Draw(GpuPipeline& pipeline, GpuVertexBuffer& buffer);
		void Draw(GpuPipeline& pipeline, GpuVertexBuffer& vertexBuffer, GpuIndexBuffer& indexBuffer);

	private:
		GpuDevice& ownerDevice;
		SDL_GPUCommandBuffer* commandBufferPtr;
		SDL_GPURenderPass* renderPassPtr;
		Color clearColor;
	};
}
