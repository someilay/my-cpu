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
)
target_sources(my-cpu PRIVATE ${BASIC_SRC})
