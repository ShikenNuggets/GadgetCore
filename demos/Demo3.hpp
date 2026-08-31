#include <GCore/FileSystem.hpp>
#include <GCore/Logger.hpp>
#include <GCore/Window.hpp>

#include <GCore/Graphics/Vertex.hpp>
#include <GCore/Graphics/GPU/GpuBuffer.hpp>
#include <GCore/Graphics/GPU/GpuCommandBuffer.hpp>
#include <GCore/Graphics/GPU/GpuDevice.hpp>
#include <GCore/Graphics/GPU/GpuPipeline.hpp>
#include <GCore/Math/Math.hpp>

namespace GadgetCoreDemos
{
	static constexpr std::array<Gadget::Vertex, 3> triangleVertices =
	{
		Gadget::Vertex(Gadget::Vector4(0.0, 0.5, 0.0, 1.0), Gadget::Color(1.0f, 0.0f, 0.0f, 1.0f)), // Top vertex
		Gadget::Vertex(Gadget::Vector4(-0.5f, -0.5f, 0.0f, 1.0), Gadget::Color(1.0f, 1.0f, 0.0f, 1.0f)), // Bottom left vertex
		Gadget::Vertex(Gadget::Vector4(0.5f, -0.5f, 0.0f, 1.0), Gadget::Color(1.0f, 0.0f, 1.0f, 1.0f)), // Bottom right vertex
	};
	static constexpr auto SizeOfTriangles = sizeof(Gadget::Vertex) * triangleVertices.size();

	static constexpr std::array<Gadget::Vertex, 8> cubeVertices =
	{
		Gadget::Vertex(Gadget::Vector4(0.0, 0.0, 0.0, 1.0), Gadget::Color(1.0f, 0.0f, 0.0f, 1.0f)),
		Gadget::Vertex(Gadget::Vector4(1.0, 0.0, 0.0, 1.0), Gadget::Color(1.0f, 1.0f, 0.0f, 1.0f)),
		Gadget::Vertex(Gadget::Vector4(0.0, 1.0, 0.0, 1.0), Gadget::Color(1.0f, 0.0f, 1.0f, 1.0f)),
		Gadget::Vertex(Gadget::Vector4(0.0, 0.0, 1.0, 1.0), Gadget::Color(1.0f, 1.0f, 1.0f, 1.0f)),
		Gadget::Vertex(Gadget::Vector4(1.0, 1.0, 0.0, 1.0), Gadget::Color(0.0f, 0.0f, 0.0f, 1.0f)),
		Gadget::Vertex(Gadget::Vector4(1.0, 0.0, 1.0, 1.0), Gadget::Color(0.0f, 1.0f, 0.0f, 1.0f)),
		Gadget::Vertex(Gadget::Vector4(0.0, 1.0, 1.0, 1.0), Gadget::Color(0.0f, 0.0f, 1.0f, 1.0f)),
		Gadget::Vertex(Gadget::Vector4(1.0, 1.0, 1.0, 1.0), Gadget::Color(0.0f, 1.0f, 1.0f, 1.0f)),
	};

	static constexpr std::array<uint32_t, 36> cubeIndices =
	{
		3, 5, 7, 7, 6, 3,
		1, 0, 2, 2, 4, 1,
		2, 6, 7, 7, 4, 2,
		0, 1, 5, 5, 3, 0,
		5, 1, 4, 4, 7, 5,
		0, 3, 6, 6, 2, 0
	};

	struct CameraBinding
	{
		Gadget::Matrix4 projection;
		Gadget::Matrix4 view;
	};

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

		bool bHoldingW = false;
		bool bHoldingS = false;
		bool bHoldingA = false;
		bool bHoldingD = false;
		bool bHolding1 = false;
		bool bHolding2 = false;
		bool bHoldingLeft = false;
		bool bHoldingRight = false;
		bool bHoldingUp = false;
		bool bHoldingDown = false;
		auto keyDownHandle = window.EventHandler().OnButtonDown.Add([&](Gadget::ButtonId buttonId)
		{
			switch (buttonId)
			{
				case Gadget::ButtonId::Keyboard_Escape:
					GADGET_LOG_INFO("Escape pressed, exiting");
					shouldContinue = false;
					break;
				case Gadget::ButtonId::Keyboard_W:
					bHoldingW = true;
					break;
				case Gadget::ButtonId::Keyboard_S:
					bHoldingS = true;
					break;
				case Gadget::ButtonId::Keyboard_A:
					bHoldingA = true;
					break;
				case Gadget::ButtonId::Keyboard_D:
					bHoldingD = true;
					break;
				case Gadget::ButtonId::Keyboard_1:
					bHolding1 = true;
					break;
				case Gadget::ButtonId::Keyboard_2:
					bHolding2 = true;
					break;
				case Gadget::ButtonId::Keyboard_Left:
					bHoldingLeft = true;
					break;
				case Gadget::ButtonId::Keyboard_Right:
					bHoldingRight = true;
					break;
				case Gadget::ButtonId::Keyboard_Up:
					bHoldingUp = true;
					break;
				case Gadget::ButtonId::Keyboard_Down:
					bHoldingDown = true;
					break;
			}
		});

		auto keyUpHandle = window.EventHandler().OnButtonUp.Add([&](Gadget::ButtonId buttonId)
		{
			switch (buttonId)
			{
				case Gadget::ButtonId::Keyboard_W:
					bHoldingW = false;
					break;
				case Gadget::ButtonId::Keyboard_S:
					bHoldingS = false;
					break;
				case Gadget::ButtonId::Keyboard_A:
					bHoldingA = false;
					break;
				case Gadget::ButtonId::Keyboard_D:
					bHoldingD = false;
					break;
				case Gadget::ButtonId::Keyboard_1:
					bHolding1 = false;
					break;
				case Gadget::ButtonId::Keyboard_2:
					bHolding2 = false;
					break;
				case Gadget::ButtonId::Keyboard_Left:
					bHoldingLeft = false;
					break;
				case Gadget::ButtonId::Keyboard_Right:
					bHoldingRight = false;
					break;
				case Gadget::ButtonId::Keyboard_Up:
					bHoldingUp = false;
					break;
				case Gadget::ButtonId::Keyboard_Down:
					bHoldingDown = false;
					break;
			}
		});

		auto* gpuDevice = window.GetGpuDevice()->GetDevice();

		auto triangleVertexBuffer = Gadget::GpuVertexBuffer(*window.GetGpuDevice(), triangleVertices);
		auto triangleIndexBuffer = Gadget::GpuIndexBuffer(*window.GetGpuDevice(), std::array<const uint32_t, 3>{ 0, 1, 2 });

		auto cubeVertexBuffer = Gadget::GpuVertexBuffer(*window.GetGpuDevice(), cubeVertices);
		auto cubeIndexBuffer = Gadget::GpuIndexBuffer(*window.GetGpuDevice(), cubeIndices);

		auto graphicsPipeline = Gadget::GpuPipeline(*window.GetGpuDevice(), "Shaders/bin/TriangleVertex.spv", "Shaders/bin/TriangleFragment.spv", 1, 0);

		CameraBinding binding;
		binding.projection = Gadget::Matrix4::PerspectiveGPU(45.0f, static_cast<float>(window.GetWidth()) / window.GetHeight(), 0.001f, 10'000.0f);
		binding.view = Gadget::Matrix4::Identity();

		Gadget::Vector3 cameraPosition = Gadget::Vector3{ 0.0f, 0.5f, 5.0f };
		Gadget::Quaternion cameraRotation;

		while (shouldContinue)
		{
			window.HandleEvents();

			static constexpr auto rotateSpeed = 0.25f;
			if (bHoldingLeft)
			{
				cameraRotation *= Gadget::Math::ToQuaternion(Gadget::Euler(0.0f, rotateSpeed, 0.0f));
			}
			else if (bHoldingRight)
			{
				cameraRotation *= Gadget::Math::ToQuaternion(Gadget::Euler(0.0f, -rotateSpeed, 0.0f));
			}

			if (bHoldingUp)
			{
				cameraRotation *= Gadget::Math::ToQuaternion(Gadget::Euler(rotateSpeed, 0.0f, 0.0f));
			}
			else if (bHoldingDown)
			{
				cameraRotation *= Gadget::Math::ToQuaternion(Gadget::Euler(-rotateSpeed, 0.0f, 0.0f));
			}

			auto asEuler = Gadget::Math::ToEuler(cameraRotation);
			asEuler.z = 0.0f; // Lock roll
			cameraRotation = Gadget::Math::ToQuaternion(asEuler);

			const auto forwardDir = cameraRotation * Gadget::Vector3::Forward();
			const auto rightDir = cameraRotation * Gadget::Vector3::Right();
			const auto upDir = Gadget::Vector3::Up();

			static constexpr auto moveSpeed = 0.01f;
			if (bHoldingW)
			{
				cameraPosition += forwardDir * moveSpeed;
			}
			else if (bHoldingS)
			{
				cameraPosition -= forwardDir * moveSpeed;
			}

			if (bHoldingA)
			{
				cameraPosition -= rightDir * moveSpeed;
			}
			else if (bHoldingD)
			{
				cameraPosition += rightDir * moveSpeed;
			}

			if (bHolding1)
			{
				cameraPosition -= upDir * moveSpeed;
			}
			else if (bHolding2)
			{
				cameraPosition += upDir * moveSpeed;
			}

			binding.view = Gadget::Math::ViewMatrix(cameraPosition, cameraRotation);

			{
				auto commandBuffer = Gadget::GpuCommandBuffer(*window.GetGpuDevice(), Gadget::Color(0.02f, 0.02f, 0.02f));
				commandBuffer.BindUniform(graphicsPipeline, 0, binding);
				commandBuffer.Draw(graphicsPipeline, cubeVertexBuffer, cubeIndexBuffer);
			}

			window.UpdateWindowSurface();
		}

		return 0;
	}
}
