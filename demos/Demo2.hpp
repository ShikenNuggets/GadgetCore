#include <GCore/Logger.hpp>
#include <GCore/Timer.hpp>
#include <GCore/Window.hpp>

namespace GadgetCoreDemos
{
	int Demo2()
	{
		Gadget::Logger::SimpleInit(Gadget::Logger::Mode::StdOut, Gadget::Logger::Severity::Verbose, {});

		auto window = Gadget::Window(800, 600, Gadget::RenderAPI::SDLRenderer, "GadgetCore Breakout Demo");
		SDL_SetRenderVSync(window.GetSDLRenderer(), SDL_RENDERER_VSYNC_ADAPTIVE);
		SDL_SetRenderLogicalPresentation(window.GetSDLRenderer(), 800, 600, SDL_LOGICAL_PRESENTATION_LETTERBOX);

		bool shouldContinue = true;
		auto quitHandle = window.EventHandler().OnQuitRequested.Add([&]()
		{
			GADGET_LOG_INFO("Application exit requested by window");
			shouldContinue = false;
		});

		bool leftInput = false;
		bool rightInput = false;
		float moveAxis = 0.0f;

		auto keyDownHandle = window.EventHandler().OnButtonDown.Add([&](Gadget::ButtonId buttonId)
		{
			switch (buttonId)
			{
				case Gadget::ButtonId::Keyboard_Escape: [[fallthrough]];
				case Gadget::ButtonId::Gamepad_Start: [[fallthrough]];
				case Gadget::ButtonId::Gamepad_Select:
					shouldContinue = false;
					break;
				case Gadget::ButtonId::Keyboard_A: [[fallthrough]];
				case Gadget::ButtonId::Keyboard_Left:
					leftInput = true;
					break;
				case Gadget::ButtonId::Keyboard_D: [[fallthrough]];
				case Gadget::ButtonId::Keyboard_Right:
					rightInput = true;
					break;
				default:
					break;
			}
		});

		auto keyUpDelegate = window.EventHandler().OnButtonUp.Add([&](Gadget::ButtonId id)
		{
			switch (id)
			{
				case Gadget::ButtonId::Keyboard_A: [[fallthrough]];
				case Gadget::ButtonId::Keyboard_Left:
					leftInput = false;
					break;
				case Gadget::ButtonId::Keyboard_D: [[fallthrough]];
				case Gadget::ButtonId::Keyboard_Right:
					rightInput = false;
					break;
				default:
					break;
			}
		});

		auto axisDelegate = window.EventHandler().OnAxisChange.Add([&](Gadget::AxisId axis, double value)
		{
			if (Gadget::Math::Abs(value) < 0.1) // Deadzone
			{
				value = 0.0;
			}

			switch (axis)
			{
				case Gadget::AxisId::Gamepad_LeftStick_Horizontal:
					moveAxis = static_cast<float>(value);
					break;
				default:
					break;
			}
		});

		float xPos = 325.0f;
		static constexpr auto moveSpeed = 250.0f;

		Gadget::Timer timer;

		int64_t numFrames = 0;
		double accumulatedTime = 0.0;
		std::optional<int64_t> cachedFramerate;

		while (shouldContinue)
		{
			timer.Update();
			const double deltaTime = timer.DeltaSeconds();

			numFrames++;
			accumulatedTime += deltaTime;
			if (accumulatedTime > 1.0)
			{
				cachedFramerate = static_cast<int64_t>(static_cast<double>(numFrames) / accumulatedTime);
				accumulatedTime -= 1.0;
				numFrames = 0;
			}

			SDL_SetRenderDrawColor(window.GetSDLRenderer(), 15, 15, 15, 0);
			SDL_RenderClear(window.GetSDLRenderer());

			window.HandleEvents();

			auto moveVal = moveAxis;
			if (leftInput)
			{
				moveVal -= 1.0f;
			}

			if (rightInput)
			{
				moveVal += 1.0f;
			}

			moveVal = Gadget::Math::Clamp(-1.0f, 1.0f, moveVal);
			xPos = Gadget::Math::Clamp(0.0f, 650.0f, xPos + (moveVal * moveSpeed * static_cast<float>(deltaTime)));

			SDL_SetRenderDrawColorFloat(window.GetSDLRenderer(), 1.0f, 1.0f, 1.0f, 1.0f);
			const SDL_FRect rect{ .x = xPos, .y = 500.0f, .w = 150.0f, .h = 25.0f };
			SDL_RenderFillRect(window.GetSDLRenderer(), &rect);

			if (cachedFramerate.has_value())
			{
				SDL_RenderDebugTextFormat(window.GetSDLRenderer(), 10, 10, "FPS: %lld", cachedFramerate.value()); // NOLINT(cppcoreguidelines-pro-type-vararg)
			}

			window.UpdateWindowSurface();
		}

		return 0;
	}
}
