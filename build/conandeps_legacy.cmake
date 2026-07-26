message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(FreeGLUT)
find_package(glew)
find_package(DevIL)
find_package(freealut)
find_package(glm)
find_package(spdlog)

set(CONANDEPS_LEGACY  FreeGLUT::freeglut_static  GLEW::GLEW  DevIL::DevIL  freealut::freealut  glm::glm-header-only  spdlog::spdlog )