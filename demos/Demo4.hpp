#include <GCore/Logger.hpp>
#include <GCore/Window.hpp>

namespace GadgetCoreDemos
{
	int Demo4()
	{
		Gadget::Logger::SimpleInit(Gadget::Logger::Mode::StdOut, Gadget::Logger::Severity::Verbose, {});

		auto window = Gadget::Window(800, 600, Gadget::RenderAPI::SDLRenderer, "Demo4 - GUI");

		bool shouldContinue = true;
		auto quitHandle = window.EventHandler().OnQuitRequested.Add([&]()
		{
			GADGET_LOG_INFO("Application exit requested by window");
			shouldContinue = false;
		});

		auto keyDownHandle = window.EventHandler().OnButtonDown.Add([&](Gadget::ButtonId buttonId)
		{
			switch (buttonId)
			{
				case Gadget::ButtonId::Keyboard_Escape:
					GADGET_LOG_INFO("Escape pressed, exiting");
					shouldContinue = false;
					break;
				case Gadget::ButtonId::Keyboard_F10:
					window.ToggleMaximize();
					break;
				case Gadget::ButtonId::Keyboard_F11:
					window.ToggleFullscreen();
					break;
				default:
					break;
			}
		});

		while (shouldContinue)
		{
			window.HandleEvents();

			SDL_SetRenderDrawColor(window.GetSDLRenderer(), 25, 25, 25, 0);
			SDL_RenderClear(window.GetSDLRenderer());

			window.UpdateWindowSurface();
		}

		return 0;
	}
}
