cmake_minimum_required (VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Platformer2DOpenGL)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 
"source/main.h"
"source/main.cpp"
"source/engine/renderer/stb_image.h"
"source/engine/renderer/ShaderRender.h"
"source/engine/renderer/ShaderRender.cpp"
"source/engine/renderer/TextureRender.h"
"source/engine/renderer/TextureRender.cpp"
"source/engine/renderer/Sprite.h"
"source/engine/renderer/Sprite.cpp"
"source/engine/renderer/AnimSprite.h"
"source/engine/renderer/AnimSprite.cpp"
"source/engine/managers/ResourcesManager.h"
"source/engine/managers/ResourcesManager.cpp"
"source/engine/managers/PhysicsManager.h"
"source/engine/managers/PhysicsManager.cpp"
"source/engine/controllers/Controller.h"
"source/engine/controllers/Controller.cpp"
"source/game/Actor.h"
"source/game/Actor.cpp"
"source/game/Pawn.h"
"source/game/Pawn.cpp"
"source/game/MainCharacter.h"
"source/game/MainCharacter.cpp"
"source/game/gameobjects/WallActor.h"
"source/game/gameobjects/WallActor.cpp"
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