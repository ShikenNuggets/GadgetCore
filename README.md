# GadgetCore - Reusable components for your next game engine
GadgetCore spawned out of work on [GadgetEngine](https://github.com/ShikenNuggets/GadgetEngine). The goal was to pull some general functionality out of that to make major refactors easier, while also making it easier to kick off new projects without wasting time either retrofitting/decoupling existing code, or rewriting everything from scratch.

## High Level Goals
- **Minimize Boilerplate**: Get new projects up and running as quickly as possible.
- **Decoupled Modules**: Use what you need, ignore what you don't. Don't pay for what you don't use.
- **Platform Abstraction**: You should never need to directly call platform-specific functions or underlying system APIs.

## Platform Support
GadgetCore officially supports Windows, Mac, Linux, and Android.

This will be expanded to include WebAssembly, game consoles, and iOS some time in the future. Most features should work on most platforms regardless of official support status. Bug reports for unsupported platforms are welcome.

## Stability
This library is in early development and is considered **unstable**. Expect frequent and unceremonious API breaks at this stage. I also do not plan to guarantee ABI stability for the foreseeable future. This will be updated as we approach a stable release.

## Usage Examples

Opening a window:
```cpp
auto window = Gadget::Window(800, 600, Gadget::RenderAPI::SDLGPU, "Example Window");
```

Handling user input:
```cpp
auto keyDownHandle = window.EventHandler().OnButtonDown.Add([&](Gadget::ButtonId buttonId)
{
	if (buttonId == Gadget::ButtonId::Keyboard_Escape)
	{
		GADGET_LOG_INFO("Escape pressed");
	}
});

// ...

window.HandleEvents();
```

3D Rendering:
```cpp
auto* gpuDevice = window.GetGpuDevice()->GetDevice();
auto vertexBuffer = Gadget::GpuVertexBuffer(gpuDevice, triangleVerts);
auto indexBuffer = Gadget::GpuIndexBuffer(gpuDevice, {{ 0, 1, 2 }});

auto graphicsPipeline = Gadget::GpuPipeline(gpuDevice, "Vertex.spv", "Fragment.spv", 0, 0);

while (true)
{
	{
		auto commandBuffer = Gadget::GpuCommandBuffer(gpuDevice, window.GetGpuDepthTexture());
		commandBuffer.Draw(graphicsPipeline, modelVertexBuffer, modelIndexBuffer);
	}

	window.UpdateWindowSurface();
}
```

## Installation
Requires:
- C++23 (GCC 14, Clang 19, MSVC 14.37)
- CMake 3.28

GadgetCore is designed to be built from source, used with CMake and FetchContent, and linked statically. You can find canonical usage examples in [GadgetEngine's experimental branch](https://github.com/ShikenNuggets/GadgetEngine/blob/Gadget2/CMakeLists.txt) or in [RenderSoft](https://github.com/ShikenNuggets/RenderSoft/blob/main/CMakeLists.txt).

Pre-built binaries and package manager distributions are not available at this time.
