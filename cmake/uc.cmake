add_library(
	uc
	SHARED
		src/uc/errors.c
		src/uc/errors/base.c
		src/uc/errors/allocation.c
		src/uc/errors/relocation.c
		src/uc/hash_map.c
)

set_target_properties(uc PROPERTIES VERSION 0.0.1)
target_include_directories(uc PRIVATE include)
