# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(jasper_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(jasper_FRAMEWORKS_FOUND_RELEASE "${jasper_FRAMEWORKS_RELEASE}" "${jasper_FRAMEWORK_DIRS_RELEASE}")

set(jasper_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET jasper_DEPS_TARGET)
    add_library(jasper_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET jasper_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${jasper_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${jasper_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:JPEG::JPEG>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### jasper_DEPS_TARGET to all of them
conan_package_library_targets("${jasper_LIBS_RELEASE}"    # libraries
                              "${jasper_LIB_DIRS_RELEASE}" # package_libdir
                              "${jasper_BIN_DIRS_RELEASE}" # package_bindir
                              "${jasper_LIBRARY_TYPE_RELEASE}"
                              "${jasper_IS_HOST_WINDOWS_RELEASE}"
                              jasper_DEPS_TARGET
                              jasper_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "jasper"    # package_name
                              "${jasper_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${jasper_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET Jasper::Jasper
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${jasper_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${jasper_LIBRARIES_TARGETS}>
                 )

    if("${jasper_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET Jasper::Jasper
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     jasper_DEPS_TARGET)
    endif()

    set_property(TARGET Jasper::Jasper
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${jasper_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET Jasper::Jasper
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${jasper_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET Jasper::Jasper
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${jasper_LIB_DIRS_RELEASE}>)
    set_property(TARGET Jasper::Jasper
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${jasper_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET Jasper::Jasper
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${jasper_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(jasper_LIBRARIES_RELEASE Jasper::Jasper)
