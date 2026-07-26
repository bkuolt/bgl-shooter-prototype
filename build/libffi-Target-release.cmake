# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(libffi_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(libffi_FRAMEWORKS_FOUND_RELEASE "${libffi_FRAMEWORKS_RELEASE}" "${libffi_FRAMEWORK_DIRS_RELEASE}")

set(libffi_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET libffi_DEPS_TARGET)
    add_library(libffi_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET libffi_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${libffi_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${libffi_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### libffi_DEPS_TARGET to all of them
conan_package_library_targets("${libffi_LIBS_RELEASE}"    # libraries
                              "${libffi_LIB_DIRS_RELEASE}" # package_libdir
                              "${libffi_BIN_DIRS_RELEASE}" # package_bindir
                              "${libffi_LIBRARY_TYPE_RELEASE}"
                              "${libffi_IS_HOST_WINDOWS_RELEASE}"
                              libffi_DEPS_TARGET
                              libffi_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "libffi"    # package_name
                              "${libffi_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${libffi_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET libffi::libffi
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${libffi_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${libffi_LIBRARIES_TARGETS}>
                 )

    if("${libffi_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET libffi::libffi
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     libffi_DEPS_TARGET)
    endif()

    set_property(TARGET libffi::libffi
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${libffi_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET libffi::libffi
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${libffi_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET libffi::libffi
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${libffi_LIB_DIRS_RELEASE}>)
    set_property(TARGET libffi::libffi
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${libffi_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET libffi::libffi
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${libffi_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(libffi_LIBRARIES_RELEASE libffi::libffi)
