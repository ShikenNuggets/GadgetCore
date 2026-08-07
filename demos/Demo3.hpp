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

		// Vertex Shader
		size_t vertexCodeSize{};
		void* vertexCode = SDL_LoadFile("Shaders/bin/TriangleVertex.spv", &vertexCodeSize);

		SDL_GPUShaderCreateInfo vertexInfo
		{
			.code_size = vertexCodeSize,
			.code = (Uint8*)vertexCode,
			.entrypoint = "main",
			.format = SDL_GPU_SHADERFORMAT_SPIRV,
			.stage = SDL_GPU_SHADERSTAGE_VERTEX,
			.num_samplers = 0,
			.num_storage_textures = 0,
			.num_storage_buffers = 0,
			.num_uniform_buffers = 0,
		};

		SDL_GPUShader* vertexShader = SDL_CreateGPUShader(gpuDevice, &vertexInfo);
		if (!vertexShader)
		{
			GADGET_LOG_ERROR("Failed to create vertex shader: {}", SDL_GetError());
			return -1;
		}

		SDL_free(vertexCode);

		// Fragment Shader
		size_t fragmentCodeSize{};
		void* fragmentCode = SDL_LoadFile("Shaders/bin/TriangleFragment.spv", &fragmentCodeSize);

		SDL_GPUShaderCreateInfo fragmentInfo
		{
			.code_size = fragmentCodeSize,
			.code = (Uint8*)fragmentCode,
			.entrypoint = "main",
			.format = SDL_GPU_SHADERFORMAT_SPIRV,
			.stage = SDL_GPU_SHADERSTAGE_FRAGMENT,
			.num_samplers = 0,
			.num_storage_textures = 0,
			.num_storage_buffers = 0,
			.num_uniform_buffers = 0,
		};

		SDL_GPUShader* fragmentShader = SDL_CreateGPUShader(gpuDevice, &fragmentInfo);
		if (!fragmentShader)
		{
			GADGET_LOG_ERROR("Failed to create fragment shader: {}", SDL_GetError());
			return -1;
		}

		SDL_free(fragmentCode);

		SDL_GPUVertexBufferDescription vertexBufferDescriptions[1]
		{{
			.slot = 0,
			.pitch = sizeof(Gadget::Vertex),
			.input_rate = SDL_GPU_VERTEXINPUTRATE_VERTEX,
			.instance_step_rate = 0
		}};

		SDL_GPUVertexAttribute vertexAttributes[2]{};
		vertexAttributes[0].buffer_slot = 0;
		vertexAttributes[0].location = 0;
		vertexAttributes[0].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3;
		vertexAttributes[0].offset = 0;

		vertexAttributes[1].buffer_slot = 0;
		vertexAttributes[1].location = 1;
		vertexAttributes[1].format = SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4;
		vertexAttributes[1].offset = sizeof(Gadget::Vector4);

		SDL_GPUColorTargetDescription colorTargetDescriptions[1]
		{{
			.format = SDL_GetGPUSwapchainTextureFormat(gpuDevice, window.GetSDLWindowPtr())
		}};

		SDL_GPUGraphicsPipelineCreateInfo pipelineInfo
		{
			.vertex_shader = vertexShader,
			.fragment_shader = fragmentShader,
			.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
		};

		pipelineInfo.vertex_input_state.num_vertex_buffers = 1;
		pipelineInfo.vertex_input_state.vertex_buffer_descriptions = vertexBufferDescriptions;
		pipelineInfo.vertex_input_state.num_vertex_attributes = 2;
		pipelineInfo.vertex_input_state.vertex_attributes = vertexAttributes;
		pipelineInfo.target_info.num_color_targets = 1;
		pipelineInfo.target_info.color_target_descriptions = colorTargetDescriptions;

		SDL_GPUGraphicsPipeline* graphicsPipeline = SDL_CreateGPUGraphicsPipeline(gpuDevice, &pipelineInfo);
		SDL_ReleaseGPUShader(gpuDevice, fragmentShader);
		SDL_ReleaseGPUShader(gpuDevice, vertexShader);

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

			SDL_BindGPUGraphicsPipeline(renderPass, graphicsPipeline);

			SDL_GPUBufferBinding bufferBindings[1]
			{{
				.buffer = triangleVertexBuffer,
				.offset = 0
			}};

			SDL_BindGPUVertexBuffers(renderPass, 0, bufferBindings, 1);

			SDL_DrawGPUPrimitives(renderPass, 3, 1, 0, 0);

			// TODO, draw something

			SDL_EndGPURenderPass(renderPass);

			SDL_SubmitGPUCommandBuffer(commandBuffer);

			window.UpdateWindowSurface();
		}

		SDL_ReleaseGPUGraphicsPipeline(gpuDevice, graphicsPipeline);

		SDL_ReleaseGPUTransferBuffer(gpuDevice, transferBuffer);
		SDL_ReleaseGPUBuffer(gpuDevice, triangleVertexBuffer);

		return 0;
	}
}
