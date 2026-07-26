########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(GLEW_FIND_QUIETLY)
    set(GLEW_MESSAGE_MODE VERBOSE)
else()
    set(GLEW_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/module-GLEWTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${glew_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(GLEW_VERSION_STRING "2.2.0")
set(GLEW_INCLUDE_DIRS ${glew_INCLUDE_DIRS_RELEASE} )
set(GLEW_INCLUDE_DIR ${glew_INCLUDE_DIRS_RELEASE} )
set(GLEW_LIBRARIES ${glew_LIBRARIES_RELEASE} )
set(GLEW_DEFINITIONS ${glew_DEFINITIONS_RELEASE} )


# Definition of extra CMake variables from cmake_extra_variables


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${glew_BUILD_MODULES_PATHS_RELEASE} )
    message(${GLEW_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


include(FindPackageHandleStandardArgs)
set(GLEW_FOUND 1)
set(GLEW_VERSION "2.2.0")

find_package_handle_standard_args(GLEW
                                  REQUIRED_VARS GLEW_VERSION
                                  VERSION_VAR GLEW_VERSION)
mark_as_advanced(GLEW_FOUND GLEW_VERSION)

set(GLEW_FOUND 1)
set(GLEW_VERSION "2.2.0")
mark_as_advanced(GLEW_FOUND GLEW_VERSION)

