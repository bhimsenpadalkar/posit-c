add_library(Utils "")

target_sources(
        Utils
        PRIVATE
        Utils.cpp
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Utils.h
)

target_include_directories(
        Utils
        PUBLIC
        Posit
        ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
        Utils
        Posit
        gtest_main
)
add_executable(
        unit_tests
        PositCreateDoubleTest.cpp
        PositCreateTest.cpp
        PositCreateFloatTest.cpp
        PositAddTest.cpp
        PositSubtractTest.cpp)

target_link_libraries(
        unit_tests
        gtest_main
        Posit
        Utils
)

add_test(
        NAME
            unit
        COMMAND
            ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)