target_link_libraries(
    dcl
    PRIVATE
        base
        uc
)

target_link_libraries(
    dcc
    PRIVATE
        base
        uc
        dcl
)

target_link_libraries(
    test
    PRIVATE
        base
        uc
        dcl
)
