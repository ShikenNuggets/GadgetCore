# CMakeList.txt : CMake project for GadgetCore, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.25)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GadgetCore" LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
	catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.11.0
)

FetchContent_MakeAvailable(catch2)

FetchContent_Declare(
	SDL3
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-3.2.26
	CMAKE_ARGS -DSDL_UNIX_CONSOLE_BUILD=ON
)

FetchContent_MakeAvailable(SDL3)

set(CMAKE_CXX_CLANG_TIDY clang-tidy)

file (GLOB_RECURSE SRC_FILES
	"src/*.cpp"
	"src/*.h"
	"src/*.hpp"
)

file (GLOB_RECURSE INC_FILES
	"include/*.h"
	"include/*.hpp"
)

add_library(GadgetCore STATIC ${SRC_FILES} ${INC_FILES})
set_property(TARGET GadgetCore PROPERTY CXX_STANDARD 23)

target_include_directories(GadgetCore PUBLIC include)

target_link_libraries(GadgetCore
	PUBLIC
		SDL3::SDL3
)

add_subdirectory(tests)
