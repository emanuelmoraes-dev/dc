target_link_libraries(
    dcl
    PRIVATE
        base
        uc
)

target_link_libraries(
    dcr
    PRIVATE
        base
        uc
        dcl
)
