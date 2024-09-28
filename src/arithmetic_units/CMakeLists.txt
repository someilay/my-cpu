set(
    BASIC_SRC 
    half_adder.c
    full_adder.c
    4_bit_adder.c
    8_bit_adder.c
    32_bit_adder.c
)
target_sources(my-cpu PRIVATE ${BASIC_SRC})
