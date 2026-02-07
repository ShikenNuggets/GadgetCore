#pragma once

#include <optional>

#include <SDL3/SDL.h>

#include "ScreenCoordinate.hpp"
#include "Graphics/Color.hpp"
#include "Graphics/WindowSurfaceView.hpp"

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

		Window(const Window& other) = delete;
		Window(Window&& other) = delete;
		Window& operator=(const Window& other) = delete;
		Window& operator=(Window&& other) = delete;

		void HandleEvents();

		WindowSurfaceView GetSurfaceView();

	private:
		SDL_Window* windowPtr = nullptr;
		ScreenCoordinate size;
		ScreenCoordinate position;
		RenderAPI renderAPI;
		std::optional<float> refreshRate;
	};
}