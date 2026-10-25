#include <GCore/Logger.hpp>
#include <GCore/Window.hpp>

#include <GCore/Graphics/GUI/GuiElement.hpp>
#include <GCore/Input/InputDefines.hpp>

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

		auto canvas = Gadget::GuiCanvas();
		auto canvasClickHandle = window.EventHandler().OnClickDown.Add([&](Gadget::ButtonId button, double x, double y)
		{
			const auto guiX = x / window.GetSize().x;
			const auto guiY = y / window.GetSize().y;

			canvas.OnClickDown(button, guiX, guiY);
		});

		auto button = canvas.AddSubElement(new Gadget::GuiElement(Gadget::GuiAnchor::MiddleCenter, 0.5f, 0.5f, &canvas));
		button->SetOnClickDownCallback([](Gadget::ButtonId button, double x, double y) -> bool
		{
			GADGET_LOG_INFO("Clicked the button!");
			return true;
		});

		while (shouldContinue)
		{
			window.HandleEvents();

			SDL_SetRenderDrawColor(window.GetSDLRenderer(), 25, 25, 25, 0);
			SDL_RenderClear(window.GetSDLRenderer());

			auto buttonBounds = button->CalculatePixelBounds(window.GetSize());

			SDL_SetRenderDrawColorFloat(window.GetSDLRenderer(), 1.0f, 1.0f, 1.0f, 1.0f);
			const SDL_FRect rect{ .x = buttonBounds.x, .y = buttonBounds.y, .w = buttonBounds.width, .h = buttonBounds.height };
			SDL_RenderFillRect(window.GetSDLRenderer(), &rect);

			window.UpdateWindowSurface();
		}

		return 0;
	}
}
