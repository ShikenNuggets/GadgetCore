# --------------------------- #
# ----- GadgetCoreDemos ----- #
# --------------------------- #
file (GLOB_RECURSE DEMO_SRC_FILES CONFIGURE_DEPENDS
	"*.cpp"
	"*.h"
	"*.hpp"
)

add_executable (GadgetCoreDemos ${DEMO_SRC_FILES})
set_target_properties(GadgetCoreDemos PROPERTIES
	CXX_EXTENSIONS NO
	CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE
	CXX_SCAN_FOR_MODULES OFF
)

target_include_directories(GadgetCoreDemos SYSTEM PRIVATE
	$<TARGET_PROPERTY:Catch2::Catch2WithMain,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(GadgetCoreDemos
	PRIVATE
		GadgetCore
		Catch2::Catch2WithMain
)
