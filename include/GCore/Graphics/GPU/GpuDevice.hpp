#pragma once

#include <SDL3/SDL.h>

namespace Gadget
{
	class GpuDevice
	{
	public:
		GpuDevice();
		~GpuDevice();

		SDL_GPUDevice* GetDevice(){ return device; }

	private:
		SDL_GPUDevice* device;
	};
}
