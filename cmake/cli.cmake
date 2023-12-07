add_executable(dcr)

target_sources(
    dcr
    PRIVATE
        src/cli/main.c
)

target_include_directories(dcr PRIVATE include)
