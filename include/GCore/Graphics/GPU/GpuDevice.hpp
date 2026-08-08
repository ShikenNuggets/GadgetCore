#pragma once

#include <span>

#include <SDL3/SDL.h>

namespace Gadget
{
	class GpuDevice
	{
	public:
		GpuDevice();
		~GpuDevice();

		SDL_GPUDevice* GetDevice(){ return device; }

		SDL_GPUBuffer* CreateVertexBuffer(std::span<const uint8_t> data);

	private:
		SDL_GPUDevice* device;
	};
}
