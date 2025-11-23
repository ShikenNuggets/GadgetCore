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

# --------------------------------------- #
# ----- Fetch External Dependencies ----- #
# --------------------------------------- #
include(FetchContent)

FetchContent_Declare(
	catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.11.0
	EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(catch2)

FetchContent_Declare(
	SDL3
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-3.2.26
	EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SDL3)

FetchContent_Declare(
	SDL3_Image
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
	GIT_TAG release-3.2.4
	EXCLUDE_FROM_ALL
)
set(SDLIMAGE_AVIF OFF) # This is on by default and gives us some nonsense unrecoverable error
FetchContent_MakeAvailable(SDL3_Image)

# --------------------------------------- #
# ------------ Setup Tooling ------------ #
# --------------------------------------- #

# Detect compiler
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(EXCEPTION_FLAG "/EHsc")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(EXCEPTION_FLAG "-fexceptions")
else()
    set(EXCEPTION_FLAG "")
endif()

find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if (CLANG_TIDY_EXE)
	message(STATUS "clang-tidy checks enabled")
	set(CMAKE_CXX_CLANG_TIDY clang-tidy "-extra-arg=${EXCEPTION_FLAG}")
else()
	message(STATUS "clang-tidy not found, will not run checks")
endif()

# --------------------------------------- #
# ------------ Setup Target ------------- #
# --------------------------------------- #
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

set_target_properties(GadgetCore PROPERTIES
	CXX_STANDARD 23
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)

target_include_directories(GadgetCore PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include/GCore
)

target_include_directories(GadgetCore PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

target_link_libraries(GadgetCore
	PUBLIC
		SDL3::SDL3
		SDL3_image::SDL3_image
)

# --------------------------- #
# ---------- Tests ---------- #
# --------------------------- #
add_subdirectory(tests)
