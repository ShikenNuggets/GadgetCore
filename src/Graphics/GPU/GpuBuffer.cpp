#include "Graphics/GPU/GpuBuffer.hpp"

using namespace Gadget;

GpuVertexBuffer::GpuVertexBuffer(GpuDevice& gpuDevice, std::span<const uint8_t> vertexData, size_t numVertices) : ownerDevice(gpuDevice), bufferPtr(nullptr), vertexCount(numVertices)
{
	bufferPtr = gpuDevice.CreateVertexBuffer(vertexData);
}

GpuVertexBuffer::GpuVertexBuffer(GpuDevice& gpuDevice, std::span<const Vertex> vertices) : ownerDevice(gpuDevice), bufferPtr(nullptr), vertexCount(vertices.size())
{
	const auto byteSpan = std::span<const uint8_t>(reinterpret_cast<const uint8_t*>(vertices.data()), vertices.size_bytes());
	bufferPtr = gpuDevice.CreateVertexBuffer(byteSpan);
}

GpuVertexBuffer::~GpuVertexBuffer()
{
	SDL_ReleaseGPUBuffer(ownerDevice.GetDevice(), bufferPtr);
}

GpuIndexBuffer::GpuIndexBuffer(GpuDevice& gpuDevice, std::span<const uint32_t> indices) : ownerDevice(gpuDevice), bufferPtr(nullptr), indexCount(indices.size())
{
	bufferPtr = gpuDevice.CreateIndexBuffer(indices);
}

GpuIndexBuffer::~GpuIndexBuffer()
{
	SDL_ReleaseGPUBuffer(ownerDevice.GetDevice(), bufferPtr);
}
