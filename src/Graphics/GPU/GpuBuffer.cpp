#include "Graphics/GPU/GpuBuffer.hpp"

using namespace Gadget;

//GpuVertexBuffer::GpuVertexBuffer(GpuDevice& gpuDevice, std::span<const uint8_t> vertexData) : ownerDevice(gpuDevice), bufferPtr(nullptr)
//{
//	bufferPtr = gpuDevice.CreateVertexBuffer(vertexData);
//}

GpuVertexBuffer::GpuVertexBuffer(GpuDevice& gpuDevice, std::span<const Vertex> vertices) : ownerDevice(gpuDevice), bufferPtr(nullptr)
{
	const auto byteSpan = std::span<const uint8_t>(reinterpret_cast<const uint8_t*>(vertices.data()), vertices.size_bytes());
	bufferPtr = gpuDevice.CreateVertexBuffer(byteSpan);
}

GpuVertexBuffer::~GpuVertexBuffer()
{
	SDL_ReleaseGPUBuffer(ownerDevice.GetDevice(), bufferPtr);
}
