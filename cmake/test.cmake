add_executable(test)

target_sources(
	test
	PRIVATE
		test/dc/lib/errors.test.c
		test/dc/lib.test.c
		test/dc.test.c
		test/main.test.c
)
target_include_directories(test PRIVATE include)
