########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(DevIL_FIND_QUIETLY)
    set(DevIL_MESSAGE_MODE VERBOSE)
else()
    set(DevIL_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/DevILTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${devil_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(DevIL_VERSION_STRING "1.8.0")
set(DevIL_INCLUDE_DIRS ${devil_INCLUDE_DIRS_RELEASE} )
set(DevIL_INCLUDE_DIR ${devil_INCLUDE_DIRS_RELEASE} )
set(DevIL_LIBRARIES ${devil_LIBRARIES_RELEASE} )
set(DevIL_DEFINITIONS ${devil_DEFINITIONS_RELEASE} )


# Definition of extra CMake variables from cmake_extra_variables


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${devil_BUILD_MODULES_PATHS_RELEASE} )
    message(${DevIL_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


