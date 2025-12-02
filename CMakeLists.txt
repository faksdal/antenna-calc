
cmake_minimum_required(VERSION 3.14)

# 1. Define the project
project(antenna-calc VERSION 0.1.0 LANGUAGES CXX)


# 2. Set C++ standard and other configurations
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)  # Stick to pure ISO C++
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For tools like clang-tidy

# (Optional) Enable warnings
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif()

# 3. Define the executable target
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/antenna-calc.cpp
    # keep adding you source files here
)

# 4. Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)


