cmake_minimum_required (VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME Project2DOpenGL)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(GAME_HEADERS
source/game/MainCharacter.h
source/game/HealthComponent.h
source/game/gameobjects/WallActor.h
source/game/gameobjects/HealActor.h
source/game/gameobjects/Hall.h
source/game/enemies/Enemy.h
source/game/enemies/MeleeEnemy.h
source/game/weapons/Bullet.h
source/game/weapons/PistolBullet.h
source/game/weapons/WeaponComponent.h
source/game/weapons/EWeaponTypes.h
)

set(GAME_CPP
source/game/MainCharacter.cpp
source/game/HealthComponent.cpp
source/game/gameobjects/WallActor.cpp
source/game/gameobjects/HealActor.cpp
source/game/gameobjects/Hall.cpp
source/game/enemies/Enemy.cpp
source/game/enemies/MeleeEnemy.cpp
source/game/weapons/Bullet.cpp
source/game/weapons/PistolBullet.cpp
source/game/weapons/WeaponComponent.cpp
)
set(ENGINE_HEADERS 
source/engine/tests/PhysicsTests.h
source/engine/renderer/stb_image.h
source/engine/Delegate.h
source/engine/renderer/ShaderRender.h
source/engine/renderer/TextureRender.h
source/engine/renderer/Sprite.h
source/engine/renderer/AnimSprite.h
source/engine/managers/ResourcesManager.h
source/engine/managers/PhysicsManager.h
source/engine/managers/GameManager.h
source/engine/managers/BSPMapGenerate.h
source/engine/AI/AStar.h
source/engine/AI/NavMesh.h
source/engine/AI/poly2tri/common/shapes.h
source/engine/AI/poly2tri/common/utils.h
source/engine/AI/poly2tri/sweep/advancing_front.h
source/engine/AI/poly2tri/sweep/cdt.h
source/engine/AI/poly2tri/sweep/sweep.h
source/engine/AI/poly2tri/sweep/sweep_context.h
source/engine/AI/poly2tri/poly2tri.h
source/engine/controllers/Controller.h
source/engine/controllers/EnemyController.h
source/engine/controllers/PlayerController.h
source/engine/physics/EPhysicsTypes.h
source/engine/physics/Collider.h
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
source/engine/managers/ResourcesManager.cpp
source/engine/managers/PhysicsManager.cpp
source/engine/managers/GameManager.cpp
source/engine/managers/BSPMapGenerate.cpp
source/engine/AI/AStar.cpp
source/engine/AI/NavMesh.cpp
source/engine/AI/poly2tri/common/shapes.cpp
source/engine/AI/poly2tri/sweep/advancing_front.cpp
source/engine/AI/poly2tri/sweep/cdt.cpp
source/engine/AI/poly2tri/sweep/sweep.cpp
source/engine/AI/poly2tri/sweep/sweep_context.cpp
source/engine/controllers/Controller.cpp
source/engine/controllers/EnemyController.cpp
source/engine/controllers/PlayerController.cpp
source/engine/physics/Collider.cpp
source/engine/default_classes/Actor.cpp
source/engine/default_classes/Pawn.cpp
source/engine/default_classes/Component.cpp
source/engine/parser/XMLParser.cpp
)
add_executable(${PROJECT_NAME} 
"source/main.cpp"
"source/main.h"
"source/AllTestCases.h"
${GAME_HEADERS}
${GAME_CPP}
${ENGINE_CPP}
${ENGINE_HEADERS}
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