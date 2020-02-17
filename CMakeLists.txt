## cmakelists_template

# run only on >3.1
cmake_minimum_required(VERSION 3.10)

# project name
project(A3_UDP_PCARS2_AxCancel VERSION 1.0)

# specify standard cxx standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include h files
include_directories(include)

# define headers
file(GLOB_RECURSE HEADERS "include/*.h")

# add source files 
file(GLOB_RECURSE SOURCES "src/*.cpp")

# make a project
add_executable(A3_UDP_PCARS2_AxCancel ${SOURCES} ${HEADERS})