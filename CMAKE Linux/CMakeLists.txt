cmake_minimum_required(VERSION 3.28)
# Change "CodeWorkspace" with the name of your project
project(CodeWorkspace C)

set(CMAKE_C_STANDARD 11)

# Linux-specific OpenMP setup
find_package(OpenMP REQUIRED)
if (OpenMP_C_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_C_LIB_NAMES}")
endif ()

add_executable(CodeWorkspace
        #<Path to C file/filename.c>
        main.c
)

# Link OpenMP to the target
if (OpenMP_C_FOUND)
    # Change "CodeWorkspace" with the name of your project
    target_link_libraries(CodeWorkspace PUBLIC OpenMP::OpenMP_C)
endif ()
