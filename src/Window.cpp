#include "Window.hpp"

#include "Logger.hpp"
#include "ThirdParty/SDL_Utils.hpp"

using namespace Gadget;

Window::Window(int32_t width_, int32_t height_, RenderAPI renderAPI_, std::string_view name, int32_t x_, int32_t y_) : size(width_, height_), position(x_, y_), renderAPI(renderAPI_)
{
	const bool didInit = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD | SDL_INIT_JOYSTICK);
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
	else if (renderAPI == RenderAPI::SDLGPU)
	{
		gpuDevice = std::make_unique<GpuDevice>();
		bool bSuccess = SDL_ClaimWindowForGPUDevice(gpuDevice->GetDevice(), windowPtr);
		if (!bSuccess)
		{
			GADGET_LOG_ERROR("Failed to claim window for GPU device, SDL Error: {}", SDL_GetError());
			// TODO - throw fatal error
		}
	}

	SDL_SetJoystickEventsEnabled(true);
	if (!SDL_JoystickEventsEnabled())
	{
		// TODO - throw fatal error
	}

	SDL_SetGamepadEventsEnabled(true);
	if (!SDL_GamepadEventsEnabled())
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
	gpuDevice.reset();

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
				size = ScreenCoordinate(e.window.data1, e.window.data2);
				eventHandler.OnWindowResized.Broadcast(e.window.data1, e.window.data2);
				break;
			case SDL_EVENT_WINDOW_MOVED:
				position = ScreenCoordinate(e.window.data1, e.window.data2);
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

				eventHandler.OnPointerMoved.Broadcast(e.motion.x, e.motion.y);

				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				eventHandler.OnButtonDown.Broadcast(SDL_Utils::MouseToButtonId(e.button.button));
				eventHandler.OnClickDown.Broadcast(SDL_Utils::MouseToButtonId(e.button.button), e.button.x, e.button.y);
				break;
			case SDL_EVENT_MOUSE_BUTTON_UP:
				eventHandler.OnButtonUp.Broadcast(SDL_Utils::MouseToButtonId(e.button.button));
				eventHandler.OnClickUp.Broadcast(SDL_Utils::MouseToButtonId(e.button.button), e.button.x, e.button.y);
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
			// SDL_EVENT_GAMEPAD_ADDED and SDL_EVENT_GAMEPAD_REMOVED are intentionally unhandled here
			case SDL_EVENT_GAMEPAD_AXIS_MOTION:
				eventHandler.OnAxisChange.Broadcast(SDL_Utils::GamepadToAxisId(e.gaxis.axis), static_cast<double>(e.gaxis.value) / std::numeric_limits<Sint16>::max());
				break;
			case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
				eventHandler.OnButtonDown.Broadcast(SDL_Utils::GamepadtoButtonId(e.gbutton.button));
				break;
			case SDL_EVENT_GAMEPAD_BUTTON_UP:
				eventHandler.OnButtonUp.Broadcast(SDL_Utils::GamepadtoButtonId(e.gbutton.button));
				break;
			case SDL_EVENT_JOYSTICK_ADDED:
				controllers.emplace(e.jdevice.which, e.jdevice.which);
				break;
			case SDL_EVENT_JOYSTICK_REMOVED:
				controllers.erase(e.jdevice.which);
				break;
			case SDL_EVENT_JOYSTICK_AXIS_MOTION:
				eventHandler.OnAxisChange.Broadcast(SDL_Utils::JoystickToAxisId(e.jaxis.axis), static_cast<double>(e.gaxis.value) / std::numeric_limits<Sint16>::max());
				break;
			case SDL_EVENT_JOYSTICK_HAT_MOTION:
				if (e.jhat.value & (SDL_HAT_LEFT | SDL_HAT_RIGHT))
				{
					eventHandler.OnAxisChange.Broadcast(SDL_Utils::JoystickHorizontalHatToAxisId(e.jhat.hat), static_cast<bool>(e.jhat.value & SDL_HAT_RIGHT) ? 1.0 : -1.0);
				}

				if (e.jhat.value & (SDL_HAT_UP | SDL_HAT_DOWN))
				{
					eventHandler.OnAxisChange.Broadcast(SDL_Utils::JoystickVerticalHatToAxisId(e.jhat.hat), static_cast<bool>(e.jhat.value & SDL_HAT_UP) ? 1.0 : -1.0);
				}

				break;
			case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
				eventHandler.OnButtonDown.Broadcast(SDL_Utils::JoystickToButtonId(e.jbutton.button));
				break;
			case SDL_EVENT_JOYSTICK_BUTTON_UP:
				eventHandler.OnButtonUp.Broadcast(SDL_Utils::JoystickToButtonId(e.jbutton.button));
				break;
			case SDL_EVENT_FINGER_DOWN:
				eventHandler.OnButtonDown.Broadcast(ButtonId::Touch_Press);
				eventHandler.OnClickDown.Broadcast(ButtonId::Touch_Press, e.button.x, e.button.y);
				break;
			case SDL_EVENT_FINGER_UP:
				eventHandler.OnButtonUp.Broadcast(ButtonId::Touch_Press);
				eventHandler.OnClickUp.Broadcast(ButtonId::Touch_Press, e.button.x, e.button.y);
				break;
			case SDL_EVENT_FINGER_MOTION:
				if (e.tfinger.dx != 0.0f)
				{
					eventHandler.OnAxisChange.Broadcast(AxisId::Touch_Horizontal, e.tfinger.dx);
				}

				if (e.tfinger.dy != 0.0f)
				{
					eventHandler.OnAxisChange.Broadcast(AxisId::Touch_Vertical, e.tfinger.dx);
				}

				eventHandler.OnPointerMoved.Broadcast(e.motion.x, e.motion.y);

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
