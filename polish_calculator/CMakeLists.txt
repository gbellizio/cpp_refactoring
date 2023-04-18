project(PolishCalculator
        VERSION 1.0.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

Include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0 # or a later release
)

FetchContent_MakeAvailable(fmt)

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