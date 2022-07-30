cmake_minimum_required (VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Platformer2DOpenGL)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 
"source/main.h"
"source/main.cpp"
"source/renderer/stb_image.h"
"source/renderer/ShaderRender.h"
"source/renderer/ShaderRender.cpp"
"source/renderer/TextureRender.h"
"source/renderer/TextureRender.cpp"
"source/renderer/Sprite.h"
"source/renderer/Sprite.cpp"
"source/renderer/AnimSprite.h"
"source/renderer/AnimSprite.cpp"
"source/managers/ResourcesManager.h"
"source/managers/ResourcesManager.cpp"
)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

include_directories(external/glm)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources)