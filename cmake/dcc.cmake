add_executable(dcc)

target_sources(
    dcc
    PRIVATE
        src/dcc/main.c
        src/dcc/logs.c
)

target_include_directories(dcc PRIVATE include)
