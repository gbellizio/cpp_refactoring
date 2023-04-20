project(PolishCalculatorTests
        VERSION 1.0.0
        LANGUAGES CXX)

include(CTest)
include(Catch)

add_executable(monopoly_tests
               test.cpp
               )

target_include_directories(monopoly_tests
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/../)

target_link_libraries(monopoly_tests PRIVATE
                      Catch2::Catch2WithMain
                      monopoly_objs
                      )

catch_discover_tests(monopoly_tests)