add_executable(dcr)

target_sources(
    dcr
    PRIVATE
        src/dcr/cli.c
)

target_include_directories(dcr PRIVATE include)
