cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
include(FetchContent)
project(OpenGL)

# set policies
set(CMAKE_POLICY_DEFAULT_CMP0148 OLD)
cmake_policy(SET CMP0135 NEW)

# set cmake variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -pg -Og -fprofile-arcs -ftest-coverage -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-s -mavx -O2")

# set glfw cmake flags
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)

# download tar releases of some libraries
FetchContent_Declare(imdialog SYSTEM URL https://github.com/aiekick/ImGuiFileDialog/archive/refs/tags/v0.6.3.tar.gz)

# git clone some libraries
FetchContent_Declare(argparse SYSTEM GIT_REPOSITORY https://github.com/p-ranav/argparse.git GIT_TAG v2.9)
FetchContent_Declare(imgui SYSTEM GIT_REPOSITORY https://github.com/ocornut/imgui.git GIT_TAG v1.88)
FetchContent_Declare(glfw SYSTEM GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.3.8)
FetchContent_Declare(glm SYSTEM GIT_REPOSITORY https://github.com/g-truc/glm GIT_TAG 0.9.9.8)
FetchContent_Declare(glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git GIT_TAG v2.0.4)
FetchContent_Declare(stb GIT_REPOSITORY https://github.com/nothings/stb.git)

# fetch the dependencies
FetchContent_MakeAvailable(argparse glad glfw glm imdialog imgui stb)

# include directories
include_directories(include ${imdialog_SOURCE_DIR} ${imgui_SOURCE_DIR} ${stb_SOURCE_DIR})

# generate glad library
add_subdirectory(${glad_SOURCE_DIR}/cmake)
glad_add_library(glad API gl:core=4.2)

# create an alternate directory for glad loading (mainly used by libraries)
add_custom_command(TARGET glad POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_BINARY_DIR}/gladsources/glad/include/glad/gl.h
    ${CMAKE_CURRENT_BINARY_DIR}/gladsources/glad/include/GL/gl.h
)

# find the necessary packages
find_package(OpenMP)

# define the source files
set(IMGUI ${imgui_SOURCE_DIR}/imgui.cpp ${imgui_SOURCE_DIR}/imgui_draw.cpp ${imgui_SOURCE_DIR}/imgui_tables.cpp ${imgui_SOURCE_DIR}/imgui_widgets.cpp)
set(IMBACKEND ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
set(IMDIALOG ${imdialog_SOURCE_DIR}/ImGuiFileDialog.cpp)

# add imgui library
add_library(imgui ${IMBACKEND} ${IMDIALOG} ${IMGUI})
target_link_libraries(imgui glad glfw)

# add template-opengl executable
add_executable(template-opengl src/buffer.cpp src/callback.cpp src/gui.cpp src/main.cpp src/mesh.cpp src/parser.cpp src/scene.cpp src/shader.cpp)
target_link_libraries(template-opengl argparse imgui glm::glm)

# link OpenMP on build type
if(OPENMP_FOUND AND ${CMAKE_BUILD_TYPE} STREQUAL Release)
    target_link_libraries(template-opengl OpenMP::OpenMP_CXX)
endif()
