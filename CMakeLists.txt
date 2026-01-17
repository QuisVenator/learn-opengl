cmake_minimum_required(VERSION 3.12)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(common/include)

add_library(glad common/src/glad.c)

# --- MAGIC ---
# 1. Find all main.cpp files in subfolders
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "projects/*/main.cpp")

# 2. Loop through them and create targets
foreach(SOURCE_FILE ${SOURCES})
    # Extract the folder name (e.g., "01_window") to use as the target name
    get_filename_component(PARENT_DIR ${SOURCE_FILE} DIRECTORY)
    get_filename_component(EXE_NAME ${PARENT_DIR} NAME)

    add_executable(${EXE_NAME} ${SOURCE_FILE})
    target_link_libraries(${EXE_NAME} PRIVATE glad glfw OpenGL::GL)
endforeach()