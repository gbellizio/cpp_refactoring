project(Monolopy
        VERSION 1.0.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(monopoly_objs OBJECT)

target_sources(monopoly_objs
               PRIVATE
               Company.cpp
               Player.cpp
               MonopolyException.cpp
               Monolopy.cpp
               )

target_link_libraries(monopoly_objs
                      PUBLIC
                      fmt::fmt)

add_executable(monopoly)

target_sources(monopoly
               PRIVATE
               main.cpp
               )

target_link_libraries(monopoly
                      PRIVATE
                      monopoly_objs
                      )

add_subdirectory(tests)