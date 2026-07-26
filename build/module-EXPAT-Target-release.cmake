# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(expat_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(expat_FRAMEWORKS_FOUND_RELEASE "${expat_FRAMEWORKS_RELEASE}" "${expat_FRAMEWORK_DIRS_RELEASE}")

set(expat_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET expat_DEPS_TARGET)
    add_library(expat_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET expat_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${expat_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${expat_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### expat_DEPS_TARGET to all of them
conan_package_library_targets("${expat_LIBS_RELEASE}"    # libraries
                              "${expat_LIB_DIRS_RELEASE}" # package_libdir
                              "${expat_BIN_DIRS_RELEASE}" # package_bindir
                              "${expat_LIBRARY_TYPE_RELEASE}"
                              "${expat_IS_HOST_WINDOWS_RELEASE}"
                              expat_DEPS_TARGET
                              expat_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "expat"    # package_name
                              "${expat_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${expat_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET EXPAT::EXPAT
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${expat_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${expat_LIBRARIES_TARGETS}>
                 )

    if("${expat_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET EXPAT::EXPAT
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     expat_DEPS_TARGET)
    endif()

    set_property(TARGET EXPAT::EXPAT
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${expat_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET EXPAT::EXPAT
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${expat_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET EXPAT::EXPAT
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${expat_LIB_DIRS_RELEASE}>)
    set_property(TARGET EXPAT::EXPAT
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${expat_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET EXPAT::EXPAT
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${expat_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(expat_LIBRARIES_RELEASE EXPAT::EXPAT)
