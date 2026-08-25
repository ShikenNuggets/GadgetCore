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

		template <typename T>
		void BindUniform(GpuPipeline& pipeline, uint32_t slot, const T& data)
		{
			BindUniformInternal(pipeline, slot, std::span<const uint8_t>{ reinterpret_cast<const uint8_t*>(&data), sizeof(T) });
		}

		template <typename T>
		void BindUniform(GpuPipeline& pipeline, uint32_t slot, std::span<const T> data)
		{
			BindUniformInternal(pipeline, slot, std::span<const uint8_t>{ reinterpret_cast<const uint8_t*>(data.data()), data.size_bytes() });
		}

		void Draw(GpuPipeline& pipeline, GpuVertexBuffer& buffer);
		void Draw(GpuPipeline& pipeline, GpuVertexBuffer& vertexBuffer, GpuIndexBuffer& indexBuffer);

	private:
		GpuDevice& ownerDevice;
		SDL_GPUCommandBuffer* commandBufferPtr;
		SDL_GPURenderPass* renderPassPtr;
		Color clearColor;

		void BindUniformInternal(GpuPipeline& pipeline, uint32_t slot, std::span<const uint8_t> data);
	};
}
