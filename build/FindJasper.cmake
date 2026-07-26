########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(Jasper_FIND_QUIETLY)
    set(Jasper_MESSAGE_MODE VERBOSE)
else()
    set(Jasper_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/module-JasperTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${jasper_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(JASPER_VERSION_STRING "4.2.4")
set(JASPER_INCLUDE_DIRS ${jasper_INCLUDE_DIRS_RELEASE} )
set(JASPER_INCLUDE_DIR ${jasper_INCLUDE_DIRS_RELEASE} )
set(JASPER_LIBRARIES ${jasper_LIBRARIES_RELEASE} )
set(JASPER_DEFINITIONS ${jasper_DEFINITIONS_RELEASE} )

set(Jasper_VERSION_STRING "4.2.4")
set(Jasper_INCLUDE_DIRS ${jasper_INCLUDE_DIRS_RELEASE} )
set(Jasper_INCLUDE_DIR ${jasper_INCLUDE_DIRS_RELEASE} )
set(Jasper_LIBRARIES ${jasper_LIBRARIES_RELEASE} )
set(Jasper_DEFINITIONS ${jasper_DEFINITIONS_RELEASE} )


# Definition of extra CMake variables from cmake_extra_variables


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${jasper_BUILD_MODULES_PATHS_RELEASE} )
    message(${Jasper_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


include(FindPackageHandleStandardArgs)
set(Jasper_FOUND 1)
set(Jasper_VERSION "4.2.4")

find_package_handle_standard_args(Jasper
                                  REQUIRED_VARS Jasper_VERSION
                                  VERSION_VAR Jasper_VERSION)
mark_as_advanced(Jasper_FOUND Jasper_VERSION)

set(JASPER_FOUND 1)
set(JASPER_VERSION "4.2.4")
mark_as_advanced(JASPER_FOUND JASPER_VERSION)
set(Jasper_FOUND 1)
set(Jasper_VERSION "4.2.4")
mark_as_advanced(Jasper_FOUND Jasper_VERSION)

