if (NOT GTEST_DIR)
    message(FATAL_ERROR "Specify GTEST_DIR!")
endif()

enable_testing()
include(GoogleTest)

add_subdirectory(${GTEST_DIR} ${GTEST_DIR}/../gtest-build)
include_directories(${GTEST_DIR}/include ${GTEST_DIR})

macro(my_cpu_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} GTest::gtest_main my-cpu)
    target_include_directories(${name} PRIVATE ${PROJECT_SOURCE_DIR}/include)
    gtest_discover_tests(${name})
endmacro()

add_subdirectory(basic)
add_subdirectory(gates)
add_subdirectory(latches)
