#include "Graphics/GPU/GpuDevice.hpp"

#include "Logger.hpp"

using namespace Gadget;

GpuDevice::GpuDevice()
{
	bool isDebug = false;
	#ifdef GADGET_DEBUG
	isDebug = true;
	#endif // GADGET_DEBUG

	device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, isDebug, nullptr);
	if (device == nullptr)
	{
		GADGET_LOG_ERROR("Unable to create GPU device! SDL Error: {}", SDL_GetError());
		// TODO - Throw fatal error
	}
}

GpuDevice::~GpuDevice()
{
	SDL_DestroyGPUDevice(device);
}
