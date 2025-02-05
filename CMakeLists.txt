cmake_minimum_required(VERSION 3.10)

project(EnvGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_FILES
    src/application.cpp

    src/render/renderer.cpp
    src/render/camera.cpp

    src/terrain/block.cpp
    src/terrain/chunk.cpp
)

set(HEADER_FILES
    src/application.hpp
    src/define.hpp

    src/utils/error.hpp
    src/utils/readfile.hpp

    src/render/renderer.hpp
    src/render/camera.hpp

    src/terrain/block.hpp
    src/terrain/chunk.hpp
)

add_executable(${PROJECT_NAME} src/main.cpp ${SRC_FILES} ${HEADER_FILES})

# Link GLFW
find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Link GLEW
find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)

# Link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

target_include_directories(${PROJECT_NAME} PRIVATE src)
