#include "Graphics/WindowSurfaceView.hpp"

#include <format>

#include "Assert.hpp"
#include "Logger.hpp"

using namespace Gadget;

WindowSurfaceView::WindowSurfaceView(SDL_Surface* surface_) : surface(surface_)
{
	GADGET_BASIC_ASSERT(surface_ != nullptr);
}

void WindowSurfaceView::Lock()
{
	GADGET_BASIC_ASSERT(surface != nullptr);

	const bool success = SDL_LockSurface(surface);
	GADGET_ASSERT(success, "Failed to lock SDL Surface. SDL Error: {}", SDL_GetError());
}

void WindowSurfaceView::Unlock()
{
	GADGET_BASIC_ASSERT(surface != nullptr);
	SDL_UnlockSurface(surface);
}

void WindowSurfaceView::Clear(const Gadget::Color& color)
{
	GADGET_BASIC_ASSERT(surface != nullptr);
	if (surface == nullptr)
	{
		return;
	}

	if (surface->pixels == nullptr)
	{
		Logger::Log(Logger::Warning, "SDL_Surface->pixels was null, cannot clear the screen");
		return;
	}

	auto* pixels = static_cast<uint32_t*>(surface->pixels);
	const auto pitchInPixels = surface->pitch / sizeof(uint32_t);
	const auto finalColor = SDL_MapSurfaceRGB(surface, static_cast<Uint8>(color.r * 255.0f), static_cast<Uint8>(color.g * 255.0f), static_cast<Uint8>(color.b * 255.0f));

	for (int y = 0; y < surface->h; y++)
	{
		for (int x = 0; x < surface->w; x++)
		{
			pixels[y * pitchInPixels + x] = finalColor;
		}
	}
}

void WindowSurfaceView::AssignPixel(int32_t x, int32_t y, Uint32 color)
{
	GADGET_BASIC_ASSERT(surface != nullptr);
	if (surface == nullptr)
	{
		return;
	}

	if (surface->pixels == nullptr)
	{
		Logger::Log(Logger::Warning, "SDL_Surface->pixels was null, cannot assign pixel");
		return;
	}

	GADGET_BASIC_ASSERT(x >= 0 && x < surface->w);
	GADGET_BASIC_ASSERT(y >= 0 && y < surface->h);
	if (x < 0 || x >= surface->w || y < 0 && y >= surface->h)
	{
		GADGET_LOG_WARNING("Tried to assign pixel with ({},{}), max width/height is ({},{})", x, y, surface->w, surface->h);
		return;
	}

	auto* pixels = static_cast<uint32_t*>(surface->pixels);
	const auto pitchInPixels = surface->pitch / sizeof(uint32_t);
	pixels[y * pitchInPixels + x] = color;
}

void WindowSurfaceView::AssignPixel(int32_t x, int32_t y, const Color& color)
{
	GADGET_BASIC_ASSERT(surface != nullptr);
	GADGET_BASIC_ASSERT(x >= 0 && x < surface->w);
	GADGET_BASIC_ASSERT(y >= 0 && y < surface->h);

	if (Math::IsNearZero(color.a) || color.a <= 0.0f)
	{
		return;
	}

	const Color sRGB = color.ToSRGB();
	const auto finalColor = SDL_MapSurfaceRGBA(surface, static_cast<Uint8>(sRGB.r * 255.0f), static_cast<Uint8>(sRGB.g * 255.0f), static_cast<Uint8>(sRGB.b * 255.0f), static_cast<Uint8>(sRGB.a * 255.0f));
	AssignPixel(x, y, finalColor);
}

int32_t WindowSurfaceView::Width() const
{
	GADGET_BASIC_ASSERT(surface != nullptr);
	if (surface == nullptr)
	{
		return -1;
	}

	return surface->w;
}

int32_t WindowSurfaceView::Height() const
{
	GADGET_BASIC_ASSERT(surface != nullptr);
	if (surface == nullptr)
	{
		return -1;
	}

	return surface->h;
}
