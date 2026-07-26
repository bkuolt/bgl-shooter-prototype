# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(wayland_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(wayland_FRAMEWORKS_FOUND_RELEASE "${wayland_FRAMEWORKS_RELEASE}" "${wayland_FRAMEWORK_DIRS_RELEASE}")

set(wayland_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET wayland_DEPS_TARGET)
    add_library(wayland_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET wayland_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${wayland_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${wayland_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:expat::expat;LibXml2::LibXml2;libffi::libffi;wayland::wayland-client>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### wayland_DEPS_TARGET to all of them
conan_package_library_targets("${wayland_LIBS_RELEASE}"    # libraries
                              "${wayland_LIB_DIRS_RELEASE}" # package_libdir
                              "${wayland_BIN_DIRS_RELEASE}" # package_bindir
                              "${wayland_LIBRARY_TYPE_RELEASE}"
                              "${wayland_IS_HOST_WINDOWS_RELEASE}"
                              wayland_DEPS_TARGET
                              wayland_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "wayland"    # package_name
                              "${wayland_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${wayland_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## COMPONENTS TARGET PROPERTIES Release ########################################

    ########## COMPONENT wayland::wayland-egl #############

        set(wayland_wayland_wayland-egl_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(wayland_wayland_wayland-egl_FRAMEWORKS_FOUND_RELEASE "${wayland_wayland_wayland-egl_FRAMEWORKS_RELEASE}" "${wayland_wayland_wayland-egl_FRAMEWORK_DIRS_RELEASE}")

        set(wayland_wayland_wayland-egl_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET wayland_wayland_wayland-egl_DEPS_TARGET)
            add_library(wayland_wayland_wayland-egl_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET wayland_wayland_wayland-egl_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'wayland_wayland_wayland-egl_DEPS_TARGET' to all of them
        conan_package_library_targets("${wayland_wayland_wayland-egl_LIBS_RELEASE}"
                              "${wayland_wayland_wayland-egl_LIB_DIRS_RELEASE}"
                              "${wayland_wayland_wayland-egl_BIN_DIRS_RELEASE}" # package_bindir
                              "${wayland_wayland_wayland-egl_LIBRARY_TYPE_RELEASE}"
                              "${wayland_wayland_wayland-egl_IS_HOST_WINDOWS_RELEASE}"
                              wayland_wayland_wayland-egl_DEPS_TARGET
                              wayland_wayland_wayland-egl_LIBRARIES_TARGETS
                              "_RELEASE"
                              "wayland_wayland_wayland-egl"
                              "${wayland_wayland_wayland-egl_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET wayland::wayland-egl
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl_LIBRARIES_TARGETS}>
                     )

        if("${wayland_wayland_wayland-egl_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET wayland::wayland-egl
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         wayland_wayland_wayland-egl_DEPS_TARGET)
        endif()

        set_property(TARGET wayland::wayland-egl APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET wayland::wayland-egl APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-egl APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl_LIB_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-egl APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET wayland::wayland-egl APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT wayland::wayland-cursor #############

        set(wayland_wayland_wayland-cursor_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(wayland_wayland_wayland-cursor_FRAMEWORKS_FOUND_RELEASE "${wayland_wayland_wayland-cursor_FRAMEWORKS_RELEASE}" "${wayland_wayland_wayland-cursor_FRAMEWORK_DIRS_RELEASE}")

        set(wayland_wayland_wayland-cursor_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET wayland_wayland_wayland-cursor_DEPS_TARGET)
            add_library(wayland_wayland_wayland-cursor_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET wayland_wayland_wayland-cursor_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-cursor_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-cursor_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-cursor_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'wayland_wayland_wayland-cursor_DEPS_TARGET' to all of them
        conan_package_library_targets("${wayland_wayland_wayland-cursor_LIBS_RELEASE}"
                              "${wayland_wayland_wayland-cursor_LIB_DIRS_RELEASE}"
                              "${wayland_wayland_wayland-cursor_BIN_DIRS_RELEASE}" # package_bindir
                              "${wayland_wayland_wayland-cursor_LIBRARY_TYPE_RELEASE}"
                              "${wayland_wayland_wayland-cursor_IS_HOST_WINDOWS_RELEASE}"
                              wayland_wayland_wayland-cursor_DEPS_TARGET
                              wayland_wayland_wayland-cursor_LIBRARIES_TARGETS
                              "_RELEASE"
                              "wayland_wayland_wayland-cursor"
                              "${wayland_wayland_wayland-cursor_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET wayland::wayland-cursor
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-cursor_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-cursor_LIBRARIES_TARGETS}>
                     )

        if("${wayland_wayland_wayland-cursor_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET wayland::wayland-cursor
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         wayland_wayland_wayland-cursor_DEPS_TARGET)
        endif()

        set_property(TARGET wayland::wayland-cursor APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-cursor_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET wayland::wayland-cursor APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-cursor_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-cursor APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-cursor_LIB_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-cursor APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-cursor_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET wayland::wayland-cursor APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-cursor_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT wayland::wayland-egl-backend #############

        set(wayland_wayland_wayland-egl-backend_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(wayland_wayland_wayland-egl-backend_FRAMEWORKS_FOUND_RELEASE "${wayland_wayland_wayland-egl-backend_FRAMEWORKS_RELEASE}" "${wayland_wayland_wayland-egl-backend_FRAMEWORK_DIRS_RELEASE}")

        set(wayland_wayland_wayland-egl-backend_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET wayland_wayland_wayland-egl-backend_DEPS_TARGET)
            add_library(wayland_wayland_wayland-egl-backend_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET wayland_wayland_wayland-egl-backend_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl-backend_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl-backend_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl-backend_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'wayland_wayland_wayland-egl-backend_DEPS_TARGET' to all of them
        conan_package_library_targets("${wayland_wayland_wayland-egl-backend_LIBS_RELEASE}"
                              "${wayland_wayland_wayland-egl-backend_LIB_DIRS_RELEASE}"
                              "${wayland_wayland_wayland-egl-backend_BIN_DIRS_RELEASE}" # package_bindir
                              "${wayland_wayland_wayland-egl-backend_LIBRARY_TYPE_RELEASE}"
                              "${wayland_wayland_wayland-egl-backend_IS_HOST_WINDOWS_RELEASE}"
                              wayland_wayland_wayland-egl-backend_DEPS_TARGET
                              wayland_wayland_wayland-egl-backend_LIBRARIES_TARGETS
                              "_RELEASE"
                              "wayland_wayland_wayland-egl-backend"
                              "${wayland_wayland_wayland-egl-backend_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET wayland::wayland-egl-backend
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl-backend_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl-backend_LIBRARIES_TARGETS}>
                     )

        if("${wayland_wayland_wayland-egl-backend_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET wayland::wayland-egl-backend
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         wayland_wayland_wayland-egl-backend_DEPS_TARGET)
        endif()

        set_property(TARGET wayland::wayland-egl-backend APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl-backend_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET wayland::wayland-egl-backend APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl-backend_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-egl-backend APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl-backend_LIB_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-egl-backend APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl-backend_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET wayland::wayland-egl-backend APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-egl-backend_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT wayland::wayland-client #############

        set(wayland_wayland_wayland-client_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(wayland_wayland_wayland-client_FRAMEWORKS_FOUND_RELEASE "${wayland_wayland_wayland-client_FRAMEWORKS_RELEASE}" "${wayland_wayland_wayland-client_FRAMEWORK_DIRS_RELEASE}")

        set(wayland_wayland_wayland-client_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET wayland_wayland_wayland-client_DEPS_TARGET)
            add_library(wayland_wayland_wayland-client_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET wayland_wayland_wayland-client_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-client_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-client_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-client_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'wayland_wayland_wayland-client_DEPS_TARGET' to all of them
        conan_package_library_targets("${wayland_wayland_wayland-client_LIBS_RELEASE}"
                              "${wayland_wayland_wayland-client_LIB_DIRS_RELEASE}"
                              "${wayland_wayland_wayland-client_BIN_DIRS_RELEASE}" # package_bindir
                              "${wayland_wayland_wayland-client_LIBRARY_TYPE_RELEASE}"
                              "${wayland_wayland_wayland-client_IS_HOST_WINDOWS_RELEASE}"
                              wayland_wayland_wayland-client_DEPS_TARGET
                              wayland_wayland_wayland-client_LIBRARIES_TARGETS
                              "_RELEASE"
                              "wayland_wayland_wayland-client"
                              "${wayland_wayland_wayland-client_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET wayland::wayland-client
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-client_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-client_LIBRARIES_TARGETS}>
                     )

        if("${wayland_wayland_wayland-client_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET wayland::wayland-client
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         wayland_wayland_wayland-client_DEPS_TARGET)
        endif()

        set_property(TARGET wayland::wayland-client APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-client_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET wayland::wayland-client APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-client_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-client APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-client_LIB_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-client APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-client_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET wayland::wayland-client APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-client_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT wayland::wayland-server #############

        set(wayland_wayland_wayland-server_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(wayland_wayland_wayland-server_FRAMEWORKS_FOUND_RELEASE "${wayland_wayland_wayland-server_FRAMEWORKS_RELEASE}" "${wayland_wayland_wayland-server_FRAMEWORK_DIRS_RELEASE}")

        set(wayland_wayland_wayland-server_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET wayland_wayland_wayland-server_DEPS_TARGET)
            add_library(wayland_wayland_wayland-server_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET wayland_wayland_wayland-server_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-server_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-server_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-server_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'wayland_wayland_wayland-server_DEPS_TARGET' to all of them
        conan_package_library_targets("${wayland_wayland_wayland-server_LIBS_RELEASE}"
                              "${wayland_wayland_wayland-server_LIB_DIRS_RELEASE}"
                              "${wayland_wayland_wayland-server_BIN_DIRS_RELEASE}" # package_bindir
                              "${wayland_wayland_wayland-server_LIBRARY_TYPE_RELEASE}"
                              "${wayland_wayland_wayland-server_IS_HOST_WINDOWS_RELEASE}"
                              wayland_wayland_wayland-server_DEPS_TARGET
                              wayland_wayland_wayland-server_LIBRARIES_TARGETS
                              "_RELEASE"
                              "wayland_wayland_wayland-server"
                              "${wayland_wayland_wayland-server_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET wayland::wayland-server
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-server_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-server_LIBRARIES_TARGETS}>
                     )

        if("${wayland_wayland_wayland-server_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET wayland::wayland-server
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         wayland_wayland_wayland-server_DEPS_TARGET)
        endif()

        set_property(TARGET wayland::wayland-server APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-server_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET wayland::wayland-server APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-server_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-server APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-server_LIB_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-server APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-server_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET wayland::wayland-server APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-server_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT wayland::wayland-scanner #############

        set(wayland_wayland_wayland-scanner_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(wayland_wayland_wayland-scanner_FRAMEWORKS_FOUND_RELEASE "${wayland_wayland_wayland-scanner_FRAMEWORKS_RELEASE}" "${wayland_wayland_wayland-scanner_FRAMEWORK_DIRS_RELEASE}")

        set(wayland_wayland_wayland-scanner_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET wayland_wayland_wayland-scanner_DEPS_TARGET)
            add_library(wayland_wayland_wayland-scanner_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET wayland_wayland_wayland-scanner_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-scanner_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-scanner_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-scanner_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'wayland_wayland_wayland-scanner_DEPS_TARGET' to all of them
        conan_package_library_targets("${wayland_wayland_wayland-scanner_LIBS_RELEASE}"
                              "${wayland_wayland_wayland-scanner_LIB_DIRS_RELEASE}"
                              "${wayland_wayland_wayland-scanner_BIN_DIRS_RELEASE}" # package_bindir
                              "${wayland_wayland_wayland-scanner_LIBRARY_TYPE_RELEASE}"
                              "${wayland_wayland_wayland-scanner_IS_HOST_WINDOWS_RELEASE}"
                              wayland_wayland_wayland-scanner_DEPS_TARGET
                              wayland_wayland_wayland-scanner_LIBRARIES_TARGETS
                              "_RELEASE"
                              "wayland_wayland_wayland-scanner"
                              "${wayland_wayland_wayland-scanner_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET wayland::wayland-scanner
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-scanner_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-scanner_LIBRARIES_TARGETS}>
                     )

        if("${wayland_wayland_wayland-scanner_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET wayland::wayland-scanner
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         wayland_wayland_wayland-scanner_DEPS_TARGET)
        endif()

        set_property(TARGET wayland::wayland-scanner APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-scanner_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET wayland::wayland-scanner APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-scanner_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-scanner APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-scanner_LIB_DIRS_RELEASE}>)
        set_property(TARGET wayland::wayland-scanner APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-scanner_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET wayland::wayland-scanner APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${wayland_wayland_wayland-scanner_COMPILE_OPTIONS_RELEASE}>)


    ########## AGGREGATED GLOBAL TARGET WITH THE COMPONENTS #####################
    set_property(TARGET wayland::wayland APPEND PROPERTY INTERFACE_LINK_LIBRARIES wayland::wayland-egl)
    set_property(TARGET wayland::wayland APPEND PROPERTY INTERFACE_LINK_LIBRARIES wayland::wayland-cursor)
    set_property(TARGET wayland::wayland APPEND PROPERTY INTERFACE_LINK_LIBRARIES wayland::wayland-egl-backend)
    set_property(TARGET wayland::wayland APPEND PROPERTY INTERFACE_LINK_LIBRARIES wayland::wayland-client)
    set_property(TARGET wayland::wayland APPEND PROPERTY INTERFACE_LINK_LIBRARIES wayland::wayland-server)
    set_property(TARGET wayland::wayland APPEND PROPERTY INTERFACE_LINK_LIBRARIES wayland::wayland-scanner)

########## For the modules (FindXXX)
set(wayland_LIBRARIES_RELEASE wayland::wayland)
