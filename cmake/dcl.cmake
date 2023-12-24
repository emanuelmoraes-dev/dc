add_library(
    dcl
    SHARED
        src/dcl/errors.c
        src/dcl/errors/base.c
        src/dcl/errors/alloc.c
        src/dcl/errors/index_out.c
        src/dcl/errors/null.c
        src/dcl/errors/not_found.c
        src/dcl/content/content_init.c
        src/dcl/content/content_alphabet.c
        src/dcl/content/content_graph.c
        src/dcl/content/content_free.c
        src/dcl/content/content_gen.c
)

set_target_properties(dcl PROPERTIES VERSION 0.0.1)
target_include_directories(dcl PRIVATE include)
