# --------------------------- #
# ----- GadgetCoreTests ----- #
# --------------------------- #
file (GLOB_RECURSE TEST_SRC_FILES
	"*.cpp"
	"*.h"
	"*.hpp"
)

add_executable (GadgetCoreTests ${TEST_SRC_FILES})
set_target_properties(GadgetCoreTests PROPERTIES CXX_EXTENSIONS NO)
target_link_libraries(GadgetCoreTests
	PRIVATE
		GadgetCore
		Catch2::Catch2WithMain
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(GadgetCoreTests)
