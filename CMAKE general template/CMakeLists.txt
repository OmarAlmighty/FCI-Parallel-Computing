cmake_minimum_required(VERSION 3.28)

# Change "CodeWorkspace" to the current project name
project(CodeWorkspace C)

set(CMAKE_C_STANDARD 11)

# Detect OS and set OpenMP flags accordingly
if (WIN32)
    # Windows-specific OpenMP setup
    find_package(OpenMP REQUIRED)
    if (OpenMP_C_FOUND)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_C_LIB_NAMES}")
    endif ()
elseif (APPLE)
    # macOS-specific OpenMP setup
    set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
    set(OpenMP_C_LIB_NAMES "omp")
    set(OpenMP_omp_LIBRARY "/opt/homebrew/Cellar/libomp/19.1.7/lib/libomp.dylib")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/homebrew/opt/libomp/lib -lomp")
elseif (UNIX)
    # Linux-specific OpenMP setup
    find_package(OpenMP REQUIRED)
    if (OpenMP_C_FOUND)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_C_LIB_NAMES}")
    endif ()
endif ()

add_executable(CodeWorkspace
        # <path to C file/filename.c>
        Lab_01/p5_1_helloOMP.c
        Lab_01/p5_4_trapz_parallel.c
)

# Link OpenMP to the target
if (OpenMP_C_FOUND)
    # Change the Project name here, "CodeWorkspace", to your current project name
    target_link_libraries(CodeWorkspace PUBLIC OpenMP::OpenMP_C)
endif ()
