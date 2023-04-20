project(PolishCalculator
        VERSION 1.0.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(polish_calculator_objs OBJECT)

target_sources(polish_calculator_objs
               PRIVATE
               parser.cpp
               solver.cpp
               solver_error.cpp
               )

target_link_libraries(polish_calculator_objs
                      PUBLIC
                      fmt::fmt-header-only)

add_executable(polish_calculator
               main.cpp
               )

target_link_libraries(polish_calculator
                      PRIVATE
                      polish_calculator_objs
                      )

add_subdirectory(tests)