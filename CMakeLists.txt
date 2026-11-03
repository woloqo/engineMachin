cmake_minimum_required(VERSION 4.0)
project(engineMachin)

add_subdirectory(glad)
add_subdirectory(glm)

set(HEADERS 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/shaderClass.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/VAO.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/VBO.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/EBO.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/colors.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/stb_image.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/textures.h"
)

set(SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/shaderClass.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VAO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VBO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/EBO.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/stb_image.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/textures.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE} ${HEADERS})

target_link_libraries(${PROJECT_NAME}
    glfw
    glad
)