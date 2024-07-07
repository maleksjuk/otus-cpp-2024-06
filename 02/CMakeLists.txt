cmake_minimum_required(VERSION 3.10)

project(ip_filter VERSION 0.0.1)

add_executable(ip_filter ip_filter.cpp)

set_target_properties(ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_compile_options(ip_filter PRIVATE
	-Wall -Wextra -pedantic -Werror
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)
