#include "Window.hpp"

#include "Logger.hpp"
#include "ThirdParty/SDL_Utils.hpp"

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

	if (renderAPI == RenderAPI::SDLRenderer)
	{
		sdlRenderer = SDL_CreateRenderer(windowPtr, nullptr);
		GADGET_ASSERT(sdlRenderer != nullptr, "Failed to create SDL Renderer! SDL Error: {}", SDL_GetError());
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

	if (renderAPI == RenderAPI::OpenGL)
	{
		glContext = SDL_GL_CreateContext(windowPtr);
		if (glContext == nullptr)
		{
			// TODO - throw fatal error
		}
	}
}

Window::~Window()
{
	if (sdlRenderer != nullptr)
	{
		SDL_DestroyRenderer(sdlRenderer);
	}

	if (glContext != nullptr)
	{
		const bool didDestroy = SDL_GL_DestroyContext(glContext);
		if (!didDestroy)
		{
			GADGET_LOG_ERROR("Failed to destroy OpenGL context! SDL Error: {}", SDL_GetError());
		}
	}

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

			// ----- Keyboard ----- //
			case SDL_EVENT_KEY_DOWN:
				eventHandler.OnButtonDown.Broadcast(SDL_Utils::KeycodeToButtonId(e.key.key));
				break;
			case SDL_EVENT_KEY_UP:
				eventHandler.OnButtonUp.Broadcast(SDL_Utils::KeycodeToButtonId(e.key.key));
				break;

			// ----- Mouse ----- //
			case SDL_EVENT_MOUSE_MOTION:
				if (e.motion.xrel != 0.0f)
				{
					eventHandler.OnAxisChange.Broadcast(AxisId::Mouse_Horizontal, e.motion.xrel);
				}
				
				if (e.motion.yrel != 0.0f)
				{
					eventHandler.OnAxisChange.Broadcast(AxisId::Mouse_Vertical, e.motion.yrel);
				}

				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				eventHandler.OnButtonDown.Broadcast(SDL_Utils::MouseToButtonId(e.button.button));
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				eventHandler.OnButtonUp.Broadcast(SDL_Utils::MouseToButtonId(e.button.button));
				break;
			case SDL_EVENT_MOUSE_WHEEL:
				if (e.wheel.x != 0.0f)
				{
					eventHandler.OnAxisChange.Broadcast(AxisId::Mouse_Scroll_Horizontal, e.wheel.x);

					if (e.wheel.x < 0.0f)
					{
						eventHandler.OnButtonDown.Broadcast(ButtonId::Mouse_Scroll_Left);
						eventHandler.OnButtonUp.Broadcast(ButtonId::Mouse_Scroll_Left);
					}
					else if (e.wheel.x > 0.0f)
					{
						eventHandler.OnButtonDown.Broadcast(ButtonId::Mouse_Scroll_Right);
						eventHandler.OnButtonUp.Broadcast(ButtonId::Mouse_Scroll_Right);
					}
				}

				if (e.wheel.y != 0.0f)
				{
					eventHandler.OnAxisChange.Broadcast(AxisId::Mouse_Scroll_Vertical, e.wheel.y);

					if (e.wheel.y > 0.0f)
					{
						eventHandler.OnButtonDown.Broadcast(ButtonId::Mouse_Scroll_Up);
						eventHandler.OnButtonUp.Broadcast(ButtonId::Mouse_Scroll_Up);
					}
					else if (e.wheel.y < 0.0f)
					{
						eventHandler.OnButtonDown.Broadcast(ButtonId::Mouse_Scroll_Down);
						eventHandler.OnButtonUp.Broadcast(ButtonId::Mouse_Scroll_Down);
					}
				}

				break;
			case SDL_EVENT_GAMEPAD_ADDED:
				OpenGamepad(e.gdevice.which);
				break;
			case SDL_EVENT_GAMEPAD_REMOVED:
				CloseGamepad(e.gdevice.which);
				break;
		}
	}
}

void Window::UpdateWindowSurface()
{
	if (sdlRenderer != nullptr)
	{
		SDL_RenderPresent(sdlRenderer);
	}

	SDL_UpdateWindowSurface(windowPtr);
}

ScreenCoordinate Window::GetSize() const noexcept
{
	return size;
}

int32_t Window::GetWidth() const noexcept
{
	return size.x;
}

int32_t Window::GetHeight() const noexcept
{
	return size.y;
}

std::optional<float> Window::GetRefreshRate() const noexcept
{
	return refreshRate;
}

WindowSurfaceView Window::GetSurfaceView()
{
	return WindowSurfaceView(SDL_GetWindowSurface(windowPtr));
}

void Window::SetSize(int32_t width, int32_t height) noexcept
{
	SetSize(ScreenCoordinate(width, height));
}

void Window::SetSize(ScreenCoordinate size_) noexcept
{
	size = size_;
	SDL_SetWindowSize(windowPtr, size.x, size.y);
}

void Window::SetWindowTitle(std::string_view title)
{
	SDL_SetWindowTitle(windowPtr, title.data());
}

void Window::OpenGamepad(SDL_JoystickID gamepadId)
{
	auto* gamepad = SDL_OpenGamepad(gamepadId);
	if (gamepad == nullptr)
	{
		GADGET_LOG_ERROR("Failed to open gamepad! SDL Error: {}", SDL_GetError());
		return;
	}
	
	gamepads.emplace(gamepadId, gamepad);
}

void Window::CloseGamepad(SDL_JoystickID gamepadId)
{
	auto gamepad = gamepads.find(gamepadId);
	if (gamepad == gamepads.end())
	{
		GADGET_LOG_ERROR("Tried to close gamepad with ID {} that was not already open!", gamepadId);
		return;
	}

	SDL_CloseGamepad(gamepad->second);

	gamepads.erase(gamepadId);
}
