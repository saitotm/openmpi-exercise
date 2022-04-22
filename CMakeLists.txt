cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

message(STATUS "set env var")
set(ENV{CC} "/usr/local/opt/llvm/bin/clang")
set(ENV{CXX} "/usr/local/opt/llvm/bin/clang++")
set(ENV{LDFLAGS} "-L/usr/local/opt/llvm/lib")
set(ENV{CPPFLAGS} "-I/usr/local/opt/llvm/include")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MatrixProduct CXX)

# Create Main project
set(SOURCES
    sample.cpp
)

set(HEADERS
    # main.h
)

add_executable(main
    ${SOURCES}
    ${HEADERS}
)

# find_package(OpenMP)
# if(OpenMP_CXX_FOUND)
# 	target_link_libraries(Main PUBLIC OpenMP::OpenMP_CXX)
# endif()

find_package(MPI REQUIRED)
message(STATUS "Run: ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS")
target_link_libraries(main PUBLIC MPI::MPI_CXX)

