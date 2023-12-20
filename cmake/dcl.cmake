add_library(
    dcl
    SHARED
        src/dcl/errors.c
        src/dcl/errors/base.c
        src/dcl/errors/alloc.c
        src/dcl/errors/index_out.c
        src/dcl/content/content_init.c
)

set_target_properties(dcl PROPERTIES VERSION 0.0.1)
target_include_directories(dcl PRIVATE include)
