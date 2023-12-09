add_executable(dc_cli)

target_sources(
    dc_cli
    PRIVATE
        src/dc/cli/main.c
)

target_include_directories(dc_cli PRIVATE include)
