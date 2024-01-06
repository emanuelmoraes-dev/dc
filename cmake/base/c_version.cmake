if (USING_MSVC)
    target_compile_options(
        base
        INTERFACE
            /std:c17
    )
elseif (USING_CLANG)
    target_compile_options(
        base
        INTERFACE
            -std=c17
    )
elseif (USING_GCC)
    target_compile_options(
        base
        INTERFACE
            -std=c17
    )
endif()
