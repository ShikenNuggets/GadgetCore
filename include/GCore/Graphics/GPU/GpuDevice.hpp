#pragma once

#include <span>

#include <SDL3/SDL.h>

#include "RawShader.hpp"

namespace Gadget
{
	class GpuDevice
	{
	public:
		GpuDevice(SDL_Window* window);
		~GpuDevice();

		SDL_GPUDevice* GetDevice(){ return device; }

		SDL_GPUShader* CreateShader(const RawShader& rawShader);
		SDL_GPUBuffer* CreateVertexBuffer(std::span<const uint8_t> data);
		SDL_GPUGraphicsPipeline* CreateGraphicsPipeline(const RawShader& rawVertexShader, const RawShader& rawFragmentShader);

	private:
		SDL_Window* ownerWindow;
		SDL_GPUDevice* device;
	};
}
