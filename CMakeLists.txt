cmake_minimum_required(VERSION 3.25)

project(C++Refactoring
        VERSION 1.0.0)

Include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0 # or a later release
)

FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.3.2 # or a later release
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

add_subdirectory(polish_calculator)
add_subdirectory(monopoly)