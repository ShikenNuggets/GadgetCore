#pragma once

#include <SDL3/SDL.h>

#include "GpuDevice.hpp"
#include "RawShader.hpp"

namespace Gadget
{
	class GpuShader
	{
	public:
		GpuShader(GpuDevice& gpuDevice, const RawShader& rawShader);
		~GpuShader();

		SDL_GPUShader* GetShader(){ return shader; }

	private:
		GpuDevice& ownerDevice;
		SDL_GPUShader* shader;
	};
}
