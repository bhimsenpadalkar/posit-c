add_executable(test_posit
        posit_create.cpp
        ../src/Posit.cpp
        ../src/Posit.h
        ./Utils.h
        ./Utils.cpp
        )

add_executable(test_posit_double
        posit_create_double.cpp
        ../src/Posit.cpp
        ../src/Posit.h
        ./Utils.h
        ./Utils.cpp
        )

add_executable(test_posit_float
        posit_create_float.cpp
        ../src/Posit.cpp
        ../src/Posit.h
        ./Utils.h
        ./Utils.cpp
        )

add_executable(test_posit_extraction
        extractFields.cpp
        ../src/Posit.cpp
        ../src/Posit.h
        ./Utils.h
        ./Utils.cpp
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

add_test(
        extractFields test_posit_extraction
)