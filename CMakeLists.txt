cmake_minimum_required(VERSION 4.0)
project(engineMachin)

add_subdirectory(glad)
add_subdirectory(glm)

find_package(Freetype REQUIRED)

set(HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/ShaderClass.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/VAO.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/VBO.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EBO.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Colors.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/stb_image.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Textures.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/TextRenderer.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Camera.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Atlas.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Block.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/MeshBuilder.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Chunk.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/World.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/Raycast.h"
)

set(SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/ShaderClass.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VAO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VBO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/EBO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/stb_image.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Textures.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/TextRenderer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Camera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Atlas.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Block.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/MeshBuilder.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Chunk.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/World.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Raycast.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_compile_definitions(${PROJECT_NAME} PRIVATE RES_PATH="${CMAKE_SOURCE_DIR}/resources/")

target_link_libraries(${PROJECT_NAME}
    glfw
    glad
    Freetype::Freetype
)