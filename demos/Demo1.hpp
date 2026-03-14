#include <print>

#include <GCore/Window.hpp>

namespace GadgetCoreDemos
{
	int Demo1()
	{
		auto window = Gadget::Window(800, 600, Gadget::RenderAPI::None, "Demo1");

		bool shouldContinue = true;
		auto quitHandle = window.EventHandler().OnQuitRequested.Add([&]()
		{
			shouldContinue = false;
		});

		auto keyDownHandle = window.EventHandler().OnButtonDown.Add([](Gadget::ButtonId buttonId)
		{
			std::println("Button pressed - button ID: {}", static_cast<uint16_t>(buttonId));
		});

		while (shouldContinue)
		{
			window.HandleEvents();
			window.UpdateWindowSurface();
		}

		return 0;
	}
}
