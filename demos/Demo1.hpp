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

		while (shouldContinue)
		{
			window.HandleEvents();
			window.UpdateWindowSurface();
		}

		return 0;
	}
}
