add_executable(test)

target_sources(
	test
	PRIVATE
		test/dcl/errors.test.c
		test/dcl.test.c
		test/main.test.c
)
target_include_directories(test PRIVATE include)
