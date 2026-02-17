# GadgetCore - Reusable components for your next game engine
GadgetCore spawned out of work on [GadgetEngine](https://github.com/ShikenNuggets/GadgetEngine). The goal was to pull some general functionality out of that to make major refactors easier, while also making it easier to kick off new projects without wasting time retrofitting/decoupling existing code.

## High Level Goals
- **Minimize Boilerplate**: Get new projects up and running as quickly as possible.
- **Decoupled Modules**: Use what you need, ignore what you don't. Don't pay for what you don't use.
- **Platform Abstraction**: You should never need to directly call a platform-specific function or an underlying system API.

## Platform Support
GadgetCore officially supports Windows, Mac, and Linux.

Official platform support will be expanded to include mobile, game consoles, and WASM some time in the future. Android is the next highest priority. That said, I expect most features to work on most platforms regardless.

## Stability
This library is in early development and is considered **unstable**. Expect frequent and unceremonious API breaks at this stage. I also do not plan to guarantee ABI stability for the foreseeable future. This will be updated as we approach a stable release.

## Installation
Requires:
- C++23 (GCC 14, Clang 18, MSVC 14.37)
- CMake 3.28

GadgetCore is designed to be built from source, used with CMake and FetchContent, and linked statically. You can find canonical usage examples in [GadgetEngine's experimental branch](https://github.com/ShikenNuggets/GadgetEngine/blob/Gadget2/CMakeLists.txt) or in [RenderSoft](https://github.com/ShikenNuggets/RenderSoft/blob/main/CMakeLists.txt).

Pre-built binaries and package manager distributions are not available at this time.
