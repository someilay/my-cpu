set(
    BASIC_SRC 
    utility.c
)
target_sources(my-cpu PRIVATE ${BASIC_SRC})

add_subdirectory(basic)
add_subdirectory(gates)
add_subdirectory(latches)
add_subdirectory(arithmetic_units)
