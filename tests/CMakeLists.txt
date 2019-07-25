add_executable(test_posit
        posit_create.cpp
        ../src/Posit.cpp
        ../src/Posit.h
        )

add_test(
        mytest test_posit
)
