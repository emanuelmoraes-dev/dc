add_executable(dcc)

target_sources(
    dcc
    PRIVATE
        src/dcc/main.c
)

target_include_directories(dcc PRIVATE include)
