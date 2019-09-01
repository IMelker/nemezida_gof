cmake_minimum_required(VERSION 3.5)

project(gof_part_1)

add_executable(abstract_factory 1_abstract_factory.cpp)
add_executable(builder 2_builder.cpp)
add_executable(dependency_injection 3_dependency_injection.cpp)
add_executable(factory_method 4_factory_method.cpp)
add_executable(lazy_initialization 5_lazy_initialization.cpp)
add_executable(multiton 6_multiton.cpp)
add_executable(object_pool 7_object_pool.cpp)
add_executable(prototype 8_prototype.cpp)
add_executable(singleton 9_singleton.cpp)

set_target_properties(abstract_factory builder dependency_injection factory_method lazy_initialization multiton object_pool prototype singleton PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
    )
