########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(libsquish_FIND_QUIETLY)
    set(libsquish_MESSAGE_MODE VERBOSE)
else()
    set(libsquish_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/libsquishTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${libsquish_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(libsquish_VERSION_STRING "1.15")
set(libsquish_INCLUDE_DIRS ${libsquish_INCLUDE_DIRS_RELEASE} )
set(libsquish_INCLUDE_DIR ${libsquish_INCLUDE_DIRS_RELEASE} )
set(libsquish_LIBRARIES ${libsquish_LIBRARIES_RELEASE} )
set(libsquish_DEFINITIONS ${libsquish_DEFINITIONS_RELEASE} )


# Definition of extra CMake variables from cmake_extra_variables


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${libsquish_BUILD_MODULES_PATHS_RELEASE} )
    message(${libsquish_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


