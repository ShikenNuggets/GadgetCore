#include <GCore/FileSystem.hpp>
#include <GCore/Logger.hpp>
#include <GCore/Window.hpp>

#include <GCore/Graphics/Vertex.hpp>
#include <GCore/Graphics/GPU/GpuBuffer.hpp>
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

		auto graphicsPipeline = Gadget::GpuPipeline(*window.GetGpuDevice(), "Shaders/bin/TriangleVertex.spv", "Shaders/bin/TriangleFragment.spv");

		while (shouldContinue)
		{
			window.HandleEvents();
			
			SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(gpuDevice);

			SDL_GPUTexture* swapchainTexture = nullptr;
			Uint32 width{};
			Uint32 height{};
			SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window.GetSDLWindowPtr(), &swapchainTexture, &width, &height); // TODO - Error handling

			SDL_GPUColorTargetInfo colorTargetInfo{
				.texture = swapchainTexture,
				.clear_color = { 15 / 255.0f, 15 / 255.0f, 15 / 255.0f, 255 / 255.0f },
				.load_op = SDL_GPU_LOADOP_CLEAR,
				.store_op = SDL_GPU_STOREOP_STORE
			};

			SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, &colorTargetInfo, 1, nullptr);

			SDL_BindGPUGraphicsPipeline(renderPass, graphicsPipeline.GetPipeline());

			SDL_GPUBufferBinding bufferBindings[1]
			{{
				.buffer = triangleVertexBuffer.GetBuffer(),
				.offset = 0
			}};

			SDL_BindGPUVertexBuffers(renderPass, 0, bufferBindings, 1);

			SDL_DrawGPUPrimitives(renderPass, 3, 1, 0, 0);

			// TODO, draw something

			SDL_EndGPURenderPass(renderPass);

			SDL_SubmitGPUCommandBuffer(commandBuffer);

			window.UpdateWindowSurface();
		}

		return 0;
	}
}
