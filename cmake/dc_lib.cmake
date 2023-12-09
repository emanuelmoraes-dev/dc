add_library(
    dc_lib
    SHARED
        src/dc/lib/content/content_init.c
        src/dc/lib/content/content_free.c
        src/dc/lib/content/content_alphabet.c
        src/dc/lib/content/content_odds.c
)

set_target_properties(dc_lib PROPERTIES VERSION 0.0.1)
target_include_directories(dc_lib PRIVATE include)
