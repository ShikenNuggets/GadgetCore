include_guard()

function(GadgetCore_SetExceptionFlag outExceptionFlagVar)
	if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
		set(${outExceptionFlagVar} "/EHsc" PARENT_SCOPE)
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		set(${outExceptionFlagVar} "-fexceptions" PARENT_SCOPE)
	else()
		set(${outExceptionFlagVar} "")
	endif()
endfunction()

function(GadgetCore_EnableClangTidy target exceptionFlagVar headerFilter)
	# TODO - See if we get clang-tidy to work reliably with Android Studio
	if (NOT ANDROID)
		find_program(CLANG_TIDY_EXE NAMES clang-tidy)

		if (CLANG_TIDY_EXE)
			set(CMAKE_CXX_CLANG_TIDY
				clang-tidy
				"-extra-arg=${exceptionFlagVar}"
				"--header-filter=${headerFilter}" 
			)
			message(STATUS "clang-tidy checks enabled")
		else()
			message(STATUS "clang-tidy not found, will not run checks")
		endif()
	endif()
endfunction()

function(GadgetCore_NoDiscardAsError target)
	target_compile_options(${target} PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:/we4834>
		$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Werror=unused-result>
	)
endfunction()

function(GadgetCore_CompileShaders TARGET_NAME)
	set(options "")
	set(oneValueArgs SRC_DIR OUT_DIR)
	set(multiValueArgs FLAGS)
	cmake_parse_arguments(PARSE_ARGV 1 ARG "${options}" "${oneValueArgs}" "${multiValueArgs}")

	if(NOT ARG_SRC_DIR OR NOT ARG_OUT_DIR)
		message(FATAL_ERROR "GadgetCore_CompileShaders requires both SRC_DIR and OUT_DIR to be specified.")
	endif()

	find_package(Vulkan REQUIRED QUIET)
	if(NOT Vulkan_GLSLC_EXECUTABLE)
		message(WARNING "glslc compiler not found! Check your Vulkan SDK installation if you require SPIR-V compilation.") # Not a fatal error since we support many platforms/use-cases that won't need this
		return()
	endif()

	file(GLOB_RECURSE SHADERS CONFIGURE_DEPENDS "${ARG_SRC_DIR}/*.glsl")
	if(NOT SHADERS)
		message(WARNING "No .glsl files found in ${ARG_SRC_DIR}")
		return()
	endif()

	file(MAKE_DIRECTORY ${ARG_OUT_DIR})
	set(SPV_OUTPUTS "")

	foreach(SHADER IN LISTS SHADERS)
		file(RELATIVE_PATH REL_PATH "${ARG_SRC_DIR}" "${SHADER}")

		get_filename_component(REL_DIR "${REL_PATH}" DIRECTORY)
        get_filename_component(SHADER_NAME "${REL_PATH}" NAME_WLE)

		set(TARGET_OUT_DIR "${ARG_OUT_DIR}/${REL_DIR}")
        file(MAKE_DIRECTORY "${TARGET_OUT_DIR}")

		set(SPV_FILE "${TARGET_OUT_DIR}/${SHADER_NAME}.spv")
		
		add_custom_command(
			OUTPUT ${SPV_FILE}
			COMMAND ${Vulkan_GLSLC_EXECUTABLE} ${ARG_FLAGS} ${SHADER} -o ${SPV_FILE}
			DEPENDS ${SHADER}
			COMMENT "Compiling ${REL_PATH}..."
		)
		
		list(APPEND SPV_OUTPUTS ${SPV_FILE})
	endforeach()

	set(SHADER_TARGET "${TARGET_NAME}_Shaders")
	add_custom_target(${SHADER_TARGET} DEPENDS ${SPV_OUTPUTS})
	add_dependencies(${TARGET_NAME} ${SHADER_TARGET})
endfunction()
