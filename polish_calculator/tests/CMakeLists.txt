project(PolishCalculatorTests
        VERSION 1.0.0
        LANGUAGES CXX)

Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(CTest)
include(Catch)

add_executable(tests
               parser_test.cpp
               solver_test.cpp
               )

target_include_directories(tests
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/../)

target_link_libraries(tests PRIVATE
                      Catch2::Catch2WithMain
                      polish_calculator_objs
                      )

catch_discover_tests(tests)