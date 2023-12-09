target_link_libraries(
    dc_lib
    PRIVATE
        base
        uc
)

target_link_libraries(
    dc_cli
    PRIVATE
        base
        uc
        dc_lib
)
