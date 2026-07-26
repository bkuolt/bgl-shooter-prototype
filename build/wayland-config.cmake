########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(wayland_FIND_QUIETLY)
    set(wayland_MESSAGE_MODE VERBOSE)
else()
    set(wayland_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/waylandTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${wayland_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(wayland_VERSION_STRING "1.22.0")
set(wayland_INCLUDE_DIRS ${wayland_INCLUDE_DIRS_RELEASE} )
set(wayland_INCLUDE_DIR ${wayland_INCLUDE_DIRS_RELEASE} )
set(wayland_LIBRARIES ${wayland_LIBRARIES_RELEASE} )
set(wayland_DEFINITIONS ${wayland_DEFINITIONS_RELEASE} )


# Definition of extra CMake variables from cmake_extra_variables


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${wayland_BUILD_MODULES_PATHS_RELEASE} )
    message(${wayland_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


