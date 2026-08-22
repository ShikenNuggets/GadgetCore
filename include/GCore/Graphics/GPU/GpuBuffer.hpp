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
		GpuVertexBuffer(GpuDevice& gpuDevice, std::span<const uint8_t> vertexData, size_t numVertices);
		GpuVertexBuffer(GpuDevice& gpuDevice, std::span<const Vertex> vertices);
		~GpuVertexBuffer();

		SDL_GPUBuffer* GetBuffer(){ return bufferPtr; }
		size_t GetVertexCount() const{ return vertexCount; }

	private:
		GpuDevice& ownerDevice;
		SDL_GPUBuffer* bufferPtr;
		size_t vertexCount;
	};

	class GpuIndexBuffer
	{
	public:
		GpuIndexBuffer(GpuDevice& gpuDevice, std::span<const uint32_t> indices);
		~GpuIndexBuffer();

		SDL_GPUBuffer* GetBuffer(){ return bufferPtr; }

	private:
		GpuDevice& ownerDevice;
		SDL_GPUBuffer* bufferPtr;
	};
}
