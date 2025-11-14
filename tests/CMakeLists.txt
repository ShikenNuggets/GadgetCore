# --------------------------- #
# ----- GadgetCoreTests ----- #
# --------------------------- #
file (GLOB_RECURSE TEST_SRC_FILES
	"*.cpp"
	"*.h"
	"*.hpp"
)

add_executable (GadgetCoreTests ${TEST_SRC_FILES})
set_property(TARGET GadgetCoreTests PROPERTY CXX_STANDARD 23)
target_link_libraries(GadgetCoreTests
	PRIVATE
		GadgetCore
		Catch2::Catch2WithMain
)
