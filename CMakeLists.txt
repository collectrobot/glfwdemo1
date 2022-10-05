## https://www.glfw.org/docs/latest/build_guide.html#build_link_cmake_package
cmake_minimum_required(VERSION 3.10)
project(demo2)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

include_directories( includes )


## set(OpenGL_GL_PREFERENCE LEGACY)
##cmake_policy (SET CMP0072 OLD)
set(OpenGL_GL_PREFERENCE LEGACY)


set( GLFW-CMAKE-STARTER-SRC
		glad.c
		main.cpp
		)

add_executable(demo2 WIN32 ${GLFW-CMAKE-STARTER-SRC} )

target_link_libraries(demo2 glfw dl m OpenGL::GL)
