#include <GCore/Logger.hpp>
#include <GCore/Window.hpp>

namespace GadgetCoreDemos
{
	int Demo1()
	{
		Gadget::Logger::SimpleInit(Gadget::Logger::Mode::StdOut, Gadget::Logger::Severity::Verbose, {});

		auto window = Gadget::Window(800, 600, Gadget::RenderAPI::None, "Demo1");

		bool shouldContinue = true;
		auto quitHandle = window.EventHandler().OnQuitRequested.Add([&]()
		{
			GADGET_LOG_INFO("Application exit requested by window");
			shouldContinue = false;
		});

		auto keyDownHandle = window.EventHandler().OnButtonDown.Add([&](Gadget::ButtonId buttonId)
		{
			GADGET_LOG_INFO("Button pressed - button ID: {}", static_cast<uint16_t>(buttonId));

			if (buttonId == Gadget::ButtonId::Keyboard_Escape)
			{
				GADGET_LOG_INFO("Escape pressed, exiting");
				shouldContinue = false;
			}
		});

		while (shouldContinue)
		{
			window.HandleEvents();
			window.UpdateWindowSurface();
		}

		return 0;
	}
}
