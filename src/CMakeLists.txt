add_library(Posit "")

target_sources(
        Posit
        PRIVATE
            Posit.cpp
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/Posit.h
        )

target_include_directories(
        Posit
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}
        )