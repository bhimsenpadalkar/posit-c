add_executable(test_posit
        posit_create.cpp
        ../src/Posit.cpp
        ../src/Posit.h
        )

add_executable(test_posit_double
        posit_create_double.cpp
        ../src/Posit.cpp
        ../src/Posit.h
        )

add_executable(test_posit_float
        posit_create_float.cpp
        ../src/Posit.cpp
        ../src/Posit.h
        )

add_test(
        creatingPositByFloat test_posit
)

add_test(
        creatingDoubleByPosit test_posit_double
)

add_test(
        creatingFloatByPosit test_posit_float
)