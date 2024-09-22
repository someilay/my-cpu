set(
    BASIC_SRC 
    half_adder.c
    full_adder.c
)
target_sources(my-cpu PRIVATE ${BASIC_SRC})
