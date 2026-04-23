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
