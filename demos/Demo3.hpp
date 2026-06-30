#include <GCore/Logger.hpp>
#include <GCore/Window.hpp>

#include <GCore/Graphics/Vertex.hpp>

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

		auto window = Gadget::Window(800, 600, Gadget::RenderAPI::SDLGPU, "Demo1");

		bool shouldContinue = true;
		auto quitHandle = window.EventHandler().OnQuitRequested.Add([&]()
		{
			GADGET_LOG_INFO("Application exit requested by window");
			shouldContinue = false;
		});

		auto keyDownHandle = window.EventHandler().OnButtonDown.Add([&](Gadget::ButtonId buttonId)
		{
			if(buttonId == Gadget::ButtonId::Keyboard_Escape)
			{
				GADGET_LOG_INFO("Escape pressed, exiting");
				shouldContinue = false;
			}
		});

		auto* gpuDevice = window.GetGpuDevice()->GetDevice();

		SDL_GPUBufferCreateInfo bufferInfo
		{
			.usage = SDL_GPU_BUFFERUSAGE_VERTEX,
			.size = SizeOfTriangles
		};
		SDL_GPUBuffer* triangleVertexBuffer = SDL_CreateGPUBuffer(gpuDevice, &bufferInfo);

		SDL_GPUTransferBufferCreateInfo transferInfo
		{
			.usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
			.size = SizeOfTriangles
		};
		SDL_GPUTransferBuffer* transferBuffer = SDL_CreateGPUTransferBuffer(gpuDevice, &transferInfo);

		auto* data = reinterpret_cast<Gadget::Vertex*>(SDL_MapGPUTransferBuffer(gpuDevice, transferBuffer, false));
		SDL_memcpy(data, triangleVertices.data(), SizeOfTriangles);
		SDL_UnmapGPUTransferBuffer(gpuDevice, transferBuffer);

		SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(gpuDevice);
		SDL_GPUCopyPass* copyPass = SDL_BeginGPUCopyPass(commandBuffer);

		SDL_GPUTransferBufferLocation location
		{
			.transfer_buffer = transferBuffer,
			.offset = 0,
		};

		SDL_GPUBufferRegion region
		{
			.buffer = triangleVertexBuffer,
			.offset = 0,
			.size = SizeOfTriangles
		};

		SDL_UploadToGPUBuffer(copyPass, &location, &region, true);

		SDL_EndGPUCopyPass(copyPass);
		SDL_SubmitGPUCommandBuffer(commandBuffer);

		while(shouldContinue)
		{
			window.HandleEvents();
			
			SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(gpuDevice);

			SDL_GPUTexture* swapchainTexture = nullptr;
			Uint32 width{};
			Uint32 height{};
			SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window.GetSDLWindowPtr(), &swapchainTexture, &width, &height); // TODO - Error handling

			SDL_GPUColorTargetInfo colorTargetInfo{
				.texture = swapchainTexture,
				.clear_color = { 240 / 255.0f, 240 / 255.0f, 240 / 255.0f, 255 / 255.0f },
				.load_op = SDL_GPU_LOADOP_CLEAR,
				.store_op = SDL_GPU_STOREOP_STORE
			};

			SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, &colorTargetInfo, 1, nullptr);

			// TODO, draw something

			SDL_EndGPURenderPass(renderPass);

			SDL_SubmitGPUCommandBuffer(commandBuffer);

			window.UpdateWindowSurface();
		}

		SDL_ReleaseGPUTransferBuffer(gpuDevice, transferBuffer);
		SDL_ReleaseGPUBuffer(gpuDevice, triangleVertexBuffer);

		return 0;
	}
}
