add_executable(dcr)

target_sources(
    dcr
    PRIVATE
        src/runner/main.c
)

target_include_directories(dcr PRIVATE include)
