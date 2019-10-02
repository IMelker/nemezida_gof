cmake_minimum_required(VERSION 3.5)

project(gof_part_3)

add_executable(chain_of_responsibility 1_chain_of_responsibility.cpp)
add_executable(command 2_command.cpp)
add_executable(command_ex 2_command_ex.cpp)
add_executable(interpreter 3_interpreter.cpp)
add_executable(iterator 4_iterator.cpp)
add_executable(mediator 5_mediator.cpp)
add_executable(memento 6_memento.cpp)
add_executable(memento_ex 6_memento_ex.cpp)
add_executable(observer 7_observer.cpp)
add_executable(state 8_state.cpp)
add_executable(strategy 9_strategy.cpp)
add_executable(template_method 10_template_method.cpp)
add_executable(visitor 11_visitor.cpp)

set_target_properties(chain_of_responsibility command command_ex interpreter iterator mediator
                      memento memento_ex observer state strategy template_method visitor PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )