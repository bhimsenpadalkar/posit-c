add_executable(
        unit_tests
        example_add.cpp
)

target_link_libraries(
        unit_tests
        gtest_main
        Posit
)

add_test(
        NAME
            unit
        COMMAND
            ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)

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