cmake_minimum_required(VERSION 3.9)
project(async)

set(CMAKE_CXX_STANDARD 14)

add_library(async SHARED src/async.cpp)

set_target_properties(
	${PROJECT_NAME}
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(${PROJECT_NAME} PUBLIC ./include)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4 /MD
    )
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

target_link_libraries(async bulk_lib)