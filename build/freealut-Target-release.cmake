# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(freealut_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(freealut_FRAMEWORKS_FOUND_RELEASE "${freealut_FRAMEWORKS_RELEASE}" "${freealut_FRAMEWORK_DIRS_RELEASE}")

set(freealut_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET freealut_DEPS_TARGET)
    add_library(freealut_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET freealut_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${freealut_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${freealut_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:OpenAL::OpenAL>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### freealut_DEPS_TARGET to all of them
conan_package_library_targets("${freealut_LIBS_RELEASE}"    # libraries
                              "${freealut_LIB_DIRS_RELEASE}" # package_libdir
                              "${freealut_BIN_DIRS_RELEASE}" # package_bindir
                              "${freealut_LIBRARY_TYPE_RELEASE}"
                              "${freealut_IS_HOST_WINDOWS_RELEASE}"
                              freealut_DEPS_TARGET
                              freealut_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "freealut"    # package_name
                              "${freealut_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${freealut_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET freealut::freealut
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${freealut_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${freealut_LIBRARIES_TARGETS}>
                 )

    if("${freealut_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET freealut::freealut
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     freealut_DEPS_TARGET)
    endif()

    set_property(TARGET freealut::freealut
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${freealut_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET freealut::freealut
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${freealut_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET freealut::freealut
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${freealut_LIB_DIRS_RELEASE}>)
    set_property(TARGET freealut::freealut
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${freealut_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET freealut::freealut
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${freealut_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(freealut_LIBRARIES_RELEASE freealut::freealut)
