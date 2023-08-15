cmake_minimum_required (VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Project2DOpenGL)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(ENGINE_HEADERS 
source/engine/math/Math.h
source/engine/tests/PhysicsTests.h
source/engine/renderer/stb_image.h
source/engine/Delegate.h
source/engine/renderer/ShaderRender.h
source/engine/renderer/TextureRender.h
source/engine/renderer/Sprite.h
source/engine/renderer/AnimSprite.h
source/engine/managers/EngineManager.h
source/engine/managers/ResourcesManager.h
source/engine/managers/PhysicsManager.h
source/engine/managers/GameManager.h
source/engine/managers/RenderManager.h
source/engine/managers/MemoryManager.h
source/engine/AI/AStarRTS.h
source/engine/AI/NavMesh.h
source/engine/UI/Widget.h
source/engine/UI/UIElement.h
source/engine/UI/Text.h
source/engine/controllers/Controller.h
source/engine/controllers/PlayerController.h
source/engine/generators/RTSMapGenerator.h
source/engine/generators/BSPMapGenerate.h
source/engine/physics/EPhysicsTypes.h
source/engine/physics/Collider.h
source/engine/physics/RaycastResult.h
source/engine/physics/PhysicsBody.h
source/engine/default_classes/Object.h
source/engine/default_classes/Actor.h
source/engine/default_classes/Pawn.h
source/engine/default_classes/Component.h
source/engine/parser/XMLParser.h
)

set(ENGINE_CPP
source/engine/renderer/ShaderRender.cpp
source/engine/renderer/TextureRender.cpp
source/engine/renderer/Sprite.cpp
source/engine/renderer/AnimSprite.cpp
source/engine/managers/EngineManager.cpp
source/engine/managers/ResourcesManager.cpp
source/engine/managers/PhysicsManager.cpp
source/engine/managers/GameManager.cpp
source/engine/managers/RenderManager.cpp
source/engine/managers/MemoryManager.cpp
source/engine/AI/AStarRTS.cpp
source/engine/AI/NavMesh.cpp
source/engine/UI/Widget.cpp
source/engine/UI/UIElement.cpp
source/engine/UI/Text.cpp
source/engine/controllers/Controller.cpp
source/engine/controllers/PlayerController.cpp
source/engine/generators/RTSMapGenerator.cpp
source/engine/generators/BSPMapGenerate.cpp
source/engine/physics/Collider.cpp
source/engine/physics/RaycastResult.cpp
source/engine/physics/PhysicsBody.cpp
source/engine/default_classes/Object.cpp
source/engine/default_classes/Actor.cpp
source/engine/default_classes/Pawn.cpp
source/engine/default_classes/Component.cpp
source/engine/parser/XMLParser.cpp
)


set(GAME_HEADERS
source/game/ResourceTypes.h
source/game/gameobjects/Unit.h
source/game/gameobjects/Goal.h
source/game/gameobjects/Wall.h
source/game/gameobjects/Resource.h
source/game/gameobjects/static/Stone.h
source/game/gameobjects/static/Wood.h
source/game/gameobjects/buildings/BuildingTypes.h
source/game/gameobjects/buildings/Building.h
source/game/gameobjects/buildings/Lumber.h
source/game/gameobjects/units/Worker.h
source/game/gameobjects/units/Lumberjack.h
)

set(GAME_CPP
source/game/gameobjects/Unit.cpp
source/game/gameobjects/Goal.cpp
source/game/gameobjects/Wall.cpp
source/game/gameobjects/Resource.cpp
source/game/gameobjects/static/Stone.cpp
source/game/gameobjects/static/Wood.cpp
source/game/gameobjects/buildings/Building.cpp
source/game/gameobjects/buildings/Lumber.cpp
source/game/gameobjects/units/Worker.cpp
source/game/gameobjects/units/Lumberjack.cpp
)

add_executable(${PROJECT_NAME} 
"source/main.cpp"
"source/main.h"
"source/AllTestCases.h"
${ENGINE_CPP}
${ENGINE_HEADERS}
${GAME_HEADERS}
${GAME_CPP}
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