cmake_minimum_required(VERSION 3.20)

project(oak CXX)

include_directories(include/oak
	dependencies
	dependencies/glm
	dependencies/imgui)

set(IMGUI_SOURCES
	dependencies/imgui/imgui.cpp
	dependencies/imgui/imgui_draw.cpp
	dependencies/imgui/imgui_widgets.cpp
	dependencies/imgui/imgui_demo.cpp
	dependencies/imgui/imgui_tables.cpp
	dependencies/imgui/backends/imgui_impl_glfw.cpp
	dependencies/imgui/backends/imgui_impl_vulkan.cpp)

add_library(oak SHARED
	source/caches.cpp
	source/camera.cpp
	source/contexts.cpp
	source/mesh.cpp
	source/polygon.cpp
	source/texture.cpp
	source/transform.cpp
	${IMGUI_SOURCES})
