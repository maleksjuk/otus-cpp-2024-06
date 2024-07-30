cmake_minimum_required(VERSION 3.10)

project(MyAllocator VERSION 0.0.1)

add_executable(MyAllocator main.cpp)

set_target_properties(MyAllocator PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_compile_options(MyAllocator PRIVATE
	-Wall -Wextra -pedantic -Werror
)

install(TARGETS MyAllocator RUNTIME DESTINATION bin)
