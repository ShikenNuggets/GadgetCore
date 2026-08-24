#include <GCore/FileSystem.hpp>
#include <GCore/Logger.hpp>
#include <GCore/Window.hpp>

#include <GCore/Graphics/Vertex.hpp>
#include <GCore/Graphics/GPU/GpuBuffer.hpp>
#include <GCore/Graphics/GPU/GpuCommandBuffer.hpp>
#include <GCore/Graphics/GPU/GpuDevice.hpp>
#include <GCore/Graphics/GPU/GpuPipeline.hpp>
#include <GCore/Graphics/GPU/GpuShader.hpp>

namespace GadgetCoreDemos
{
	static constexpr std::array<Gadget::Vertex, 3> triangleVertices =
	{
		Gadget::Vertex(Gadget::Vector4(0.0, 0.5, 0.0, 1.0), Gadget::Color(1.0f, 0.0f, 0.0f, 1.0f)), // Top vertex
		Gadget::Vertex(Gadget::Vector4(-0.5f, -0.5f, 0.0f, 1.0), Gadget::Color(1.0f, 1.0f, 0.0f, 1.0f)), // Bottom left vertex
		Gadget::Vertex(Gadget::Vector4(0.5f, -0.5f, 0.0f, 1.0), Gadget::Color(1.0f, 0.0f, 1.0f, 1.0f)), // Bottom right vertex
	};
	static constexpr auto SizeOfTriangles = sizeof(Gadget::Vertex) * triangleVertices.size();

	int Demo3()
	{
		Gadget::Logger::SimpleInit(Gadget::Logger::Mode::StdOut, Gadget::Logger::Severity::Verbose, {});

		auto window = Gadget::Window(800, 600, Gadget::RenderAPI::SDLGPU, "Demo3");

		bool shouldContinue = true;
		auto quitHandle = window.EventHandler().OnQuitRequested.Add([&]()
		{
			GADGET_LOG_INFO("Application exit requested by window");
			shouldContinue = false;
		});

		auto keyDownHandle = window.EventHandler().OnButtonDown.Add([&](Gadget::ButtonId buttonId)
		{
			if (buttonId == Gadget::ButtonId::Keyboard_Escape)
			{
				GADGET_LOG_INFO("Escape pressed, exiting");
				shouldContinue = false;
			}
		});

		auto* gpuDevice = window.GetGpuDevice()->GetDevice();

		auto triangleVertexBuffer = Gadget::GpuVertexBuffer(*window.GetGpuDevice(), triangleVertices);
		auto triangleIndexBuffer = Gadget::GpuIndexBuffer(*window.GetGpuDevice(), std::array<const uint32_t, 3>{ 0, 1, 2 });

		auto graphicsPipeline = Gadget::GpuPipeline(*window.GetGpuDevice(), "Shaders/bin/TriangleVertex.spv", "Shaders/bin/TriangleFragment.spv");

		while (shouldContinue)
		{
			window.HandleEvents();

			{
				auto commandBuffer = Gadget::GpuCommandBuffer(*window.GetGpuDevice(), Gadget::Color(0.02f, 0.02f, 0.02f));
				commandBuffer.Draw(graphicsPipeline, triangleVertexBuffer, triangleIndexBuffer);
			}

			window.UpdateWindowSurface();
		}

		return 0;
	}
}
