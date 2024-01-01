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
set(CMAKE_CXX_FLAGS_RELEASE "-s -mavx -O3")

# static link on windows
if (WIN32)
    string(APPEND CMAKE_CXX_FLAGS_RELEASE " -mwindows -static")
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " -mwindows -static")
endif()

# set glfw cmake flags
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)

# git clone some libraries
FetchContent_Declare(objloader SYSTEM GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader.git GIT_TAG cc327eecf7f8f4139932aec8d75db2d091f412ef)
FetchContent_Declare(imdialog SYSTEM GIT_REPOSITORY https://github.com/aiekick/ImGuiFileDialog.git GIT_TAG 8371c8612ddfe9b23464ba9b02770ea046e81f98)
FetchContent_Declare(argparse SYSTEM GIT_REPOSITORY https://github.com/p-ranav/argparse.git GIT_TAG 69dabd88a8e6680b1a1a18397eb3e165e4019ce6)
FetchContent_Declare(implot SYSTEM GIT_REPOSITORY https://github.com/epezent/implot.git GIT_TAG 065acc3319f0422479c0fed5a5edccd0f563729f)
FetchContent_Declare(imgui SYSTEM GIT_REPOSITORY https://github.com/ocornut/imgui.git GIT_TAG 1ab63d925f21e03be7735661500e5b914dd93c19)
FetchContent_Declare(glad SYSTEM GIT_REPOSITORY https://github.com/Dav1dde/glad.git GIT_TAG 2348b07c1ab4504d60398713781d8a57880234fa)
FetchContent_Declare(stb SYSTEM GIT_REPOSITORY https://github.com/nothings/stb.git GIT_TAG beebb24b945efdea3b9bba23affb8eb3ba8982e7)
FetchContent_Declare(glfw SYSTEM GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3eaf1255b29fdf5c2895856c7be7d7185ef2b241)
FetchContent_Declare(glm SYSTEM GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 47585fde0c49fa77a2bf2fb1d2ead06999fd4b6e)

# fetch the dependencies
FetchContent_MakeAvailable(argparse glad glfw glm imdialog imgui objloader stb)

# include directories
include_directories(include ${imdialog_SOURCE_DIR} ${imgui_SOURCE_DIR} ${objloader_SOURCE_DIR} ${stb_SOURCE_DIR})

# generate glad library
add_subdirectory(${glad_SOURCE_DIR}/cmake)
glad_add_library(glad API gl:core=4.2)

# create an alternate directory for glad loading (mainly used by libraries)
add_custom_command(TARGET glad POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_BINARY_DIR}/gladsources/glad/include/glad/gl.h
    ${CMAKE_CURRENT_BINARY_DIR}/gladsources/glad/include/GL/gl.h
)

# include headers for imdialog library
target_include_directories(ImGuiFileDialog PUBLIC ${imgui_SOURCE_DIR})

# find the necessary packages
find_package(OpenMP)

# define the source files
set(IMGUI ${imgui_SOURCE_DIR}/imgui.cpp ${imgui_SOURCE_DIR}/imgui_draw.cpp ${imgui_SOURCE_DIR}/imgui_tables.cpp ${imgui_SOURCE_DIR}/imgui_widgets.cpp)
set(IMBACKEND ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp)
set(IMDIALOG ${imdialog_SOURCE_DIR}/ImGuiFileDialog.cpp)

# add imgui library
add_library(imgui ${IMBACKEND} ${IMDIALOG} ${IMGUI} ${objloader_SOURCE_DIR}/tiny_obj_loader.cc)
target_link_libraries(imgui glad glfw)

# add template-opengl executable
add_executable(template-opengl src/buffer.cpp src/callback.cpp src/gui.cpp src/main.cpp src/material.cpp src/mesh.cpp src/parser.cpp src/scene.cpp src/shader.cpp)
target_link_libraries(template-opengl argparse imgui glm::glm)

# link OpenMP on build type
if(OPENMP_FOUND AND ${CMAKE_BUILD_TYPE} STREQUAL Release)
    target_link_libraries(template-opengl OpenMP::OpenMP_CXX)
endif()
