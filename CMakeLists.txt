cmake_minimum_required(VERSION 3.20)
project(bgl_shooter_prototype C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-g)

find_package(FreeGLUT REQUIRED)
find_package(glew REQUIRED)
find_package(DevIL REQUIRED)
find_package(freealut REQUIRED)
find_package(OpenAL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/audio
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gfx
    ${CMAKE_CURRENT_SOURCE_DIR}/src/input
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math
    ${CMAKE_CURRENT_SOURCE_DIR}/src/physics
)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.hpp"
)

add_executable(bgl-shooter ${SOURCES})

target_link_libraries(bgl-shooter
    PRIVATE
    FreeGLUT::freeglut_static
    GLEW::GLEW
    DevIL::DevIL
    DevIL::ILUT
    DevIL::ILU
    DevIL::IL
    freealut::freealut
    OpenAL::OpenAL
    OpenGL::GL
    OpenGL::GLU
    glm::glm-header-only
    spdlog::spdlog
    ${CMAKE_DL_LIBS}
)
