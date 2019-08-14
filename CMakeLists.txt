cmake_minimum_required(VERSION 3.7)

project(imgui_entt_entity_editor CXX)

add_library(imgui_entt_entity_editor INTERFACE)

target_include_directories(imgui_entt_entity_editor INTERFACE
	"${CMAKE_CURRENT_SOURCE_DIR}"
)



