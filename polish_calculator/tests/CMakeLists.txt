project(PolishCalculatorTests
        VERSION 1.0.0
        LANGUAGES CXX)

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