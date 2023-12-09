add_library(
    dcl
    SHARED
        src/dcl/content/content_init.c
        src/dcl/content/content_free.c
        src/dcl/content/content_alphabet.c
        src/dcl/content/content_odds.c
)

set_target_properties(dcl PROPERTIES VERSION 0.0.1)

target_include_directories(dcl PRIVATE include)
