# --------------------------- #
# ----- GadgetCoreDemos ----- #
# --------------------------- #
file (GLOB_RECURSE DEMO_SRC_FILES CONFIGURE_DEPENDS
	"*.cpp"
	"*.h"
	"*.hpp"
)

if (ANDROID)
	set(APP_TARGET main)
	add_library(${APP_TARGET} SHARED ${DEMO_SRC_FILES})
else()
	set(APP_TARGET GadgetCoreDemos)
	add_executable(${APP_TARGET} ${DEMO_SRC_FILES})
endif()

GadgetCore_CompileShaders(${APP_TARGET}
	SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/src"
	OUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Shaders/bin"
	FLAGS -g -O0
)

set_target_properties(${APP_TARGET} PROPERTIES
	CXX_EXTENSIONS NO
	CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE
	CXX_SCAN_FOR_MODULES OFF
)

target_include_directories(${APP_TARGET} SYSTEM PRIVATE
	$<TARGET_PROPERTY:Catch2::Catch2WithMain,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(${APP_TARGET}
	PRIVATE
		GadgetCore
		Catch2::Catch2WithMain
)

if (ANDROID)
	add_library(app-glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
	target_link_libraries(${APP_TARGET} PRIVATE app-glue)
endif()

# --------------------------------------- #
# --------- Asset Deployment ------------ #
# --------------------------------------- #
add_custom_command(TARGET ${APP_TARGET} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/Shaders/bin"
		"$<TARGET_FILE_DIR:${APP_TARGET}>/Shaders/bin"
)
