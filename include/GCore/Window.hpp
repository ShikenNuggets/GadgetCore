#pragma once

#include <optional>

#include <SDL3/SDL.h>

#include "ScreenCoordinate.hpp"

namespace Gadget
{
	enum class RenderAPI : uint8_t
	{
		None,
		SDLGPU,
		OpenGL,
		Metal,
		Vulkan,
		DX11,
		DX12,

		RenderAPI_Max
	};

	class Window
	{
	public:
		Window(int32_t width_, int32_t height_, RenderAPI renderAPI_, int32_t x_ = 0, int32_t y_ = 0);
		~Window();

		void HandleEvents();

	private:
		SDL_Window* windowPtr;
		ScreenCoordinate size;
		ScreenCoordinate position;
		RenderAPI renderAPI;
		std::optional<float> refreshRate;
	};
}