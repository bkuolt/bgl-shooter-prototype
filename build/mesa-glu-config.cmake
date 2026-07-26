########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(mesa-glu_FIND_QUIETLY)
    set(mesa-glu_MESSAGE_MODE VERBOSE)
else()
    set(mesa-glu_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/mesa-gluTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${mesa-glu_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(mesa-glu_VERSION_STRING "9.0.3")
set(mesa-glu_INCLUDE_DIRS ${mesa-glu_INCLUDE_DIRS_RELEASE} )
set(mesa-glu_INCLUDE_DIR ${mesa-glu_INCLUDE_DIRS_RELEASE} )
set(mesa-glu_LIBRARIES ${mesa-glu_LIBRARIES_RELEASE} )
set(mesa-glu_DEFINITIONS ${mesa-glu_DEFINITIONS_RELEASE} )


# Definition of extra CMake variables from cmake_extra_variables


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${mesa-glu_BUILD_MODULES_PATHS_RELEASE} )
    message(${mesa-glu_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


