target_link_libraries(
    dcl
    PRIVATE
        base
)

target_link_libraries(
    dcr
    PRIVATE
        base
        dcl
)
