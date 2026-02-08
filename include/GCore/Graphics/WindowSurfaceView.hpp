#pragma once

#include <SDL3/SDL.h>

#include "Color.hpp"

namespace Gadget
{
	class WindowSurfaceView
	{
	public:
		explicit WindowSurfaceView(SDL_Surface* surface_);

		void Lock();
		void Unlock();

		void Clear(const Color& color = Color::Black());
		void AssignPixel(int32_t x, int32_t y, Uint32 color);
		void AssignPixel(int32_t x, int32_t y, const Color& color);

		[[nodiscard]] int32_t Width() const;
		[[nodiscard]] int32_t Height() const;

	private:
		SDL_Surface* surface;
	};
}
