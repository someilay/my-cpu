set(
    BASIC_SRC 
    not.c 
    and.c
    or.c
)
target_sources(my-cpu PRIVATE ${BASIC_SRC})
