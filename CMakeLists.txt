cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE GLVND)

# Find Packages automatically
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Setup Includes
include_directories(common/include)

# Compile GLAD once
add_library(glad common/src/glad.c)

# Function to easily create a new lesson
# usage: create_lesson(001-create-a-window)
function(create_lesson name)
    add_executable(${name} projects/${name}/main.cpp)
    target_link_libraries(${name} PRIVATE glad glfw OpenGL::GL)
endfunction()

# --- DEFINING PROJECTS ---
create_lesson(001-create-a-window)
create_lesson(002-hello-triangle)
create_lesson(003-hello-rectangle)