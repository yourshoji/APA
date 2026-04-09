# 1. Minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# 2. Project Name and Version
project(APA VERSION 1.0)

# 3. Specify the C standard (Modern C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 4. Add the executable (Project Name + your source file)
# Replace 'main.c' with whatever your filename is
add_executable(APA main.c)

# 5. Optional: Add compiler warnings (shows you care about code quality)
if(MSVC)
    target_compile_options(APA PRIVATE /W4)
else()
    target_compile_options(APA PRIVATE -Wall -Wextra -Wpedantic)
endif()