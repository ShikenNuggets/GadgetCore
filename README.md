# GadgetCore - A library of reusable components for your next game engine project.
GadgetCore spawned out of work on my own game engine, [GadgetEngine](https://github.com/ShikenNuggets/GadgetEngine). The goal was to pull some of the more general functionality out of that to make major refactors easier, while also making it easier and faster to kick off new projects without needing to spend a bunch of time retrofitting and decoupling code.

## High Level Goals
- **Mimize boilerplate**: Get new projects up and running as quickly as possible.
- **Decoupled Modules**: Use the components that you need, ignore the ones you don't.
- **Platform Abstraction**: You can call underlying system APIs when absolutely necessary, but you shouldn't have to.

## Stability
This library is currently considered **unstable**. I don't intend to break the API frequently but I can't make any promises at this time. I also do not plan to guarantee ABI stability for the foreseeable future. This will be updated as we get closer to a proper stable release.

## Installation

Requires:
- C++23
- CMake 3.28

GadgetCore is designed to be used with CMake and FetchContent. See [the CMakeLists in GadgetEngine's experimental Gadget2 branch](https://github.com/ShikenNuggets/GadgetEngine/blob/Gadget2/CMakeLists.txt) for the canonical usage example.

