#clang -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp -o my_program main.c
#gcc-14 -o main -fopenmp main.c

#================= Global =================#
cmake_minimum_required(VERSION 3.28)
project(CodeWorkspace C)

set(CMAKE_C_STANDARD 11)

# Specify OpenMP flags and libraries
set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include")
set(OpenMP_C_LIB_NAMES "omp")
set(OpenMP_omp_LIBRARY "/opt/homebrew/Cellar/libomp/19.1.7/lib/libomp.dylib")

# Find OpenMP
find_package(OpenMP REQUIRED)

# Add OpenMP flags to the compiler
if (OpenMP_C_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif ()


add_executable(CodeWorkspace
#        Lab_01/p5_4_trapz_parallel.c
        Lab_01/p5_1_helloOMP.c
#        InClass/program.c
#        Lab_01/p5_2_helloOMP_ErrorHandle.c
#        Lab_01/p5_3_trapz_serial.c
#        Lab_01/p5_5_trapz_parallel_bad.c
#        Lab_01/p5_6_trapz_parallel_fix.c
#        Lab_01/p5_7_trapz_parallel_reduction.c
#        Lab_01/p5_8_trapz_parallel_for.c
#        Lab_01/p5_9_bad_for_loop.c
#        Lab_01/p5_10_bad_fibonacci.c
#        Lab_01/p5_11_PI_serial.c
#        Lab_01/p5_12_PI_parallel_inaccurate.c
#        Lab_01/p5_13_PI_parallel_accurate.c
#        Lab_01/p5_14_PI_parallel_default.c
)


# Link OpenMP to the target
if (OpenMP_C_FOUND)
    target_link_libraries(CodeWorkspace PUBLIC OpenMP::OpenMP_C)
endif ()
