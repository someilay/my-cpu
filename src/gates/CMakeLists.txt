set(
    BASIC_SRC 
    xor.c
    and_4.c
    or_4.c
    mpx.c
    mpx_4.c
    dmpx.c
    dmpx_4.c
    nor.c
    32_and_32.c
    32_or_32.c
    32_not_32.c
    32_mpx_32.c
    32_mpx_4_32.c
)
target_sources(my-cpu PRIVATE ${BASIC_SRC})
