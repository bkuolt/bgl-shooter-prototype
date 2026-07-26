# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(lcms_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(lcms_FRAMEWORKS_FOUND_RELEASE "${lcms_FRAMEWORKS_RELEASE}" "${lcms_FRAMEWORK_DIRS_RELEASE}")

set(lcms_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET lcms_DEPS_TARGET)
    add_library(lcms_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET lcms_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${lcms_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${lcms_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### lcms_DEPS_TARGET to all of them
conan_package_library_targets("${lcms_LIBS_RELEASE}"    # libraries
                              "${lcms_LIB_DIRS_RELEASE}" # package_libdir
                              "${lcms_BIN_DIRS_RELEASE}" # package_bindir
                              "${lcms_LIBRARY_TYPE_RELEASE}"
                              "${lcms_IS_HOST_WINDOWS_RELEASE}"
                              lcms_DEPS_TARGET
                              lcms_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "lcms"    # package_name
                              "${lcms_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${lcms_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET lcms::lcms
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${lcms_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${lcms_LIBRARIES_TARGETS}>
                 )

    if("${lcms_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET lcms::lcms
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     lcms_DEPS_TARGET)
    endif()

    set_property(TARGET lcms::lcms
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${lcms_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET lcms::lcms
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${lcms_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET lcms::lcms
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${lcms_LIB_DIRS_RELEASE}>)
    set_property(TARGET lcms::lcms
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${lcms_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET lcms::lcms
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${lcms_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(lcms_LIBRARIES_RELEASE lcms::lcms)
