gcovr --html --html-details --root .. --gcov-executable "gcov-14" \
	--exclude-directories ".*_deps/.*" \
	--exclude-directories ".*CompilerId.*" \
	--exclude ".*catch2.*/*.hpp" \
	--exclude ".*/.*Tests.cpp" \
	-o "out/coverage_report/_report.html"
