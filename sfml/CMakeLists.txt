cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
project(SFML)

# set cmake variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -pg -Og -fprofile-arcs -ftest-coverage -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-s -mavx -O3")

# static link on windows
if (WIN32)
    string(APPEND CMAKE_CXX_FLAGS_RELEASE " -mwindows -static")
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " -mwindows -static")
endif()

# set SFML link to static
set(BUILD_SHARED_LIBS FALSE)

# git clone some dependencies
FetchContent_Declare(argparse SYSTEM GIT_REPOSITORY https://github.com/p-ranav/argparse.git GIT_TAG v2.9)
FetchContent_Declare(sfml SYSTEM GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.1)

# fetch the dependencies
FetchContent_MakeAvailable(argparse sfml)

# include directories
include_directories(include)

# find the necessary packages
find_package(OpenMP)

# add template-opengl executable
add_executable(template-sfml src/main.cpp)
target_link_libraries(template-sfml argparse sfml-graphics)

# link OpenMP on build type
if(OPENMP_FOUND AND ${CMAKE_BUILD_TYPE} STREQUAL Release)
    target_link_libraries(template-sfml OpenMP::OpenMP_CXX)
endif()
