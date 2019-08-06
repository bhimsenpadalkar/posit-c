add_executable(all_tests
        tests.cpp
        ../src/Posit.cpp
        ../src/Posit.h
        ./Utils.h
        ./Utils.cpp
        PositAddTest.h
        PositAddTest.cpp
        ./Testable.h
        ./PositCreateTest.cpp
        ./PositCreateTest.h
        PositCreateDoubleTest.cpp
        PositCreateDoubleTest.h
        PositCreateFloatTest.cpp
        PositCreateFloatTest.h
        )

add_test(all_tests all_tests)