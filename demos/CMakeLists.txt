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
