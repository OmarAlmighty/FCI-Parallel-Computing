#gcc-14 -o main -fopenmp main.c
#gcc -o main -fopenmp main.c

#================= Global =================#
cmake_minimum_required(VERSION 3.28)

# Change "CodeWorkspace" with the name of your project
project(CodeWorkspace C)

set(CMAKE_C_STANDARD 11)

# Find OpenMP
find_package(OpenMP REQUIRED)

# Add OpenMP flags to the compiler
if (OpenMP_C_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif ()

add_executable(CodeWorkspace
        #<Path to C file/filename.c>
        main.c
)

# Link OpenMP to the target
if (OpenMP_C_FOUND)
    target_link_libraries(CodeWorkspace PUBLIC OpenMP::OpenMP_C)
endif ()