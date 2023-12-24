add_library(
	uc
	SHARED
		src/uc/errors.c
		src/uc/errors/base.c
		src/uc/errors/alloc.c
		src/uc/errors/realloc.c
		src/uc/errors/not_found.c
		src/uc/errors/empty.c
		src/uc/errors/overflow.c
		src/uc/hash_map.c
		src/uc/list.c
		src/uc/quick_sort.c
)

set_target_properties(uc PROPERTIES VERSION 0.0.1)
target_include_directories(uc PRIVATE include)
