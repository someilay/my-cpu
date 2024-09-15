set(
    BASIC_SRC 
    sr_latch.c
    d_latch.c
    d_flip_flop.c
)
target_sources(my-cpu PRIVATE ${BASIC_SRC})
