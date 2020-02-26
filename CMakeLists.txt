## @file   cmakelists for a3-udp-chair-cancel-axes
## @author Benjamin Williams <bwilliams@lincoln.ac.uk>

# run only on >3.9
cmake_minimum_required(VERSION 3.9)

set(PROJECT_NAME "A3_UDP_PCARS2_AxCancel")

# project name
project(${PROJECT_NAME} VERSION 1.0)

# specify standard cxx standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include h files
include_directories(include)

# define headers
file(GLOB_RECURSE HEADERS "include/*.h")

# add source files 
file(GLOB_RECURSE SOURCES "src/*.cpp")

# copy assets folder to build
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)

# make a project
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# put in sdl nuget packages
set_property(TARGET ${PROJECT_NAME}
    PROPERTY VS_PACKAGE_REFERENCES "sdl2_2.0.5"
	PROPERTY VS_PACKAGE_REFERENCES "sdl2_ttf.nuget_"
)

# Find nuget
# find_program(NUGET nuget)

# if(NOT NUGET)
	# # error
	# message(FATAL "Cannot find nuget command line tool.")
# else()
	# # call restore
	# execute_process(COMMAND ${NUGET} restore ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.sln)
# endif()


