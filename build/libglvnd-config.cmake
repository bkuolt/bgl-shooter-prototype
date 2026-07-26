########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(libglvnd_FIND_QUIETLY)
    set(libglvnd_MESSAGE_MODE VERBOSE)
else()
    set(libglvnd_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/libglvndTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${libglvnd_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(libglvnd_VERSION_STRING "1.7.0")
set(libglvnd_INCLUDE_DIRS ${libglvnd_INCLUDE_DIRS_RELEASE} )
set(libglvnd_INCLUDE_DIR ${libglvnd_INCLUDE_DIRS_RELEASE} )
set(libglvnd_LIBRARIES ${libglvnd_LIBRARIES_RELEASE} )
set(libglvnd_DEFINITIONS ${libglvnd_DEFINITIONS_RELEASE} )


# Definition of extra CMake variables from cmake_extra_variables


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${libglvnd_BUILD_MODULES_PATHS_RELEASE} )
    message(${libglvnd_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


