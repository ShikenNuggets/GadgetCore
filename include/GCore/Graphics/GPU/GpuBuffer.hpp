#pragma once

#include <span>

#include <SDL3/SDL.h>

#include "GpuDevice.hpp"
#include "GCore/Graphics/Vertex.hpp"

namespace Gadget
{
	class GpuVertexBuffer
	{
	public:
		GpuVertexBuffer(GpuDevice& gpuDevice, std::span<const uint8_t> vertexData);
		GpuVertexBuffer(GpuDevice& gpuDevice, std::span<const Vertex> vertices);
		~GpuVertexBuffer();

		SDL_GPUBuffer* GetBuffer(){ return bufferPtr; }

	private:
		GpuDevice& ownerDevice;
		SDL_GPUBuffer* bufferPtr;
	};
}
