add_library(
    dcl
    SHARED
        src/lib/content/content_init.c
        src/lib/content/content_free.c
)

set_target_properties(dcl PROPERTIES VERSION 0.0.1)

target_include_directories(dcl PRIVATE include)