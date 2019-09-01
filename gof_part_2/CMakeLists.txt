cmake_minimum_required(VERSION 3.5)

project(gof_part_2)

add_executable(adapter 1_adapter.cpp)
add_executable(bridge 2_bridge.cpp)
add_executable(composite 3_composite.cpp)
add_executable(decorator 4_decorator.cpp)
add_executable(facade 5_facade.cpp)
add_executable(flyweight 6_flyweight.cpp)
add_executable(proxy 7_proxy.cpp)

set_target_properties(adapter bridge composite decorator facade flyweight proxy PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )
