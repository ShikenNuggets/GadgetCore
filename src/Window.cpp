#include "Window.hpp"

#include "Logger.hpp"

using namespace Gadget;

Window::Window(int32_t width_, int32_t height_, RenderAPI renderAPI_, std::string_view name, int32_t x_, int32_t y_) : size(width_, height_), position(x_, y_), renderAPI(renderAPI_)
{
	const bool didInit = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD);
	if (didInit)
	{
		// TODO - throw fatal error
	}

	Uint32 windowFlags = SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_RESIZABLE;
	if (renderAPI == RenderAPI::OpenGL)
	{
		windowFlags |= SDL_WINDOW_OPENGL;
	}

	if (position.x == 0 && position.y == 0)
	{
		position.x = SDL_WINDOWPOS_CENTERED;
		position.y = SDL_WINDOWPOS_CENTERED;
	}

	windowPtr = SDL_CreateWindow(name.data(), size.x, size.y, windowFlags);
	if (windowPtr == nullptr)
	{
		// TODO - throw fatal error
	}

	SDL_SetJoystickEventsEnabled(true);
	if (!SDL_JoystickEventsEnabled())
	{
		// TODO - throw fatal error
	}

	const auto displayId = SDL_GetPrimaryDisplay();
	if (displayId == 0)
	{
		GADGET_LOG_WARNING("Could not get primary display ID! SDL Error: {}", SDL_GetError());
	}
	else
	{
		const auto* displayMode = SDL_GetCurrentDisplayMode(displayId);
		if (displayMode == nullptr)
		{
			GADGET_LOG_WARNING("Could not get primary display mode! SDL Error: {}", SDL_GetError());
		}
		else if (displayMode->refresh_rate != 0.0f)
		{
			refreshRate = displayMode->refresh_rate;
		}
	}
}

Window::~Window()
{
	if (windowPtr != nullptr)
	{
		SDL_DestroyWindow(windowPtr);
	}

	SDL_Quit();
}

void Window::HandleEvents()
{
	SDL_Event e{};
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_EVENT_QUIT:
				eventHandler.OnQuitRequested.Broadcast();
				return; // No need to process any other events
			case SDL_EVENT_WINDOW_RESIZED:
				eventHandler.OnWindowResized.Broadcast(e.window.data1, e.window.data2);
				break;
			case SDL_EVENT_WINDOW_MOVED:
				eventHandler.OnWindowMoved.Broadcast(e.window.data1, e.window.data2);
				break;
			case SDL_EVENT_KEY_DOWN:
				eventHandler.OnKeyDown.Broadcast(); // TODO - Pass keycode
				break;
			case SDL_EVENT_KEY_UP:
				eventHandler.OnKeyUp.Broadcast(); // TODO - Pass keycode
				break;
		}
	}
}

WindowSurfaceView Window::GetSurfaceView()
{
	return WindowSurfaceView(SDL_GetWindowSurface(windowPtr));
}

void Window::UpdateWindowSurface()
{
	SDL_UpdateWindowSurface(windowPtr);
}

void Window::SetWindowTitle(std::string_view title)
{
	SDL_SetWindowTitle(windowPtr, title.data());
}
