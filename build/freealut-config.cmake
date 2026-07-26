########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(freealut_FIND_QUIETLY)
    set(freealut_MESSAGE_MODE VERBOSE)
else()
    set(freealut_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/freealutTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${freealut_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(freealut_VERSION_STRING "1.1.0")
set(freealut_INCLUDE_DIRS ${freealut_INCLUDE_DIRS_RELEASE} )
set(freealut_INCLUDE_DIR ${freealut_INCLUDE_DIRS_RELEASE} )
set(freealut_LIBRARIES ${freealut_LIBRARIES_RELEASE} )
set(freealut_DEFINITIONS ${freealut_DEFINITIONS_RELEASE} )


# Definition of extra CMake variables from cmake_extra_variables


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${freealut_BUILD_MODULES_PATHS_RELEASE} )
    message(${freealut_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


