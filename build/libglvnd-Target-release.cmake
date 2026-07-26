# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(libglvnd_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(libglvnd_FRAMEWORKS_FOUND_RELEASE "${libglvnd_FRAMEWORKS_RELEASE}" "${libglvnd_FRAMEWORK_DIRS_RELEASE}")

set(libglvnd_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET libglvnd_DEPS_TARGET)
    add_library(libglvnd_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET libglvnd_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${libglvnd_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${libglvnd_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:libglvnd::gldispatch;xorg::x11;xorg-proto::glproto;libglvnd::glx>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### libglvnd_DEPS_TARGET to all of them
conan_package_library_targets("${libglvnd_LIBS_RELEASE}"    # libraries
                              "${libglvnd_LIB_DIRS_RELEASE}" # package_libdir
                              "${libglvnd_BIN_DIRS_RELEASE}" # package_bindir
                              "${libglvnd_LIBRARY_TYPE_RELEASE}"
                              "${libglvnd_IS_HOST_WINDOWS_RELEASE}"
                              libglvnd_DEPS_TARGET
                              libglvnd_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "libglvnd"    # package_name
                              "${libglvnd_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${libglvnd_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## COMPONENTS TARGET PROPERTIES Release ########################################

    ########## COMPONENT libglvnd::gl #############

        set(libglvnd_libglvnd_gl_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(libglvnd_libglvnd_gl_FRAMEWORKS_FOUND_RELEASE "${libglvnd_libglvnd_gl_FRAMEWORKS_RELEASE}" "${libglvnd_libglvnd_gl_FRAMEWORK_DIRS_RELEASE}")

        set(libglvnd_libglvnd_gl_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET libglvnd_libglvnd_gl_DEPS_TARGET)
            add_library(libglvnd_libglvnd_gl_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET libglvnd_libglvnd_gl_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gl_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gl_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gl_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'libglvnd_libglvnd_gl_DEPS_TARGET' to all of them
        conan_package_library_targets("${libglvnd_libglvnd_gl_LIBS_RELEASE}"
                              "${libglvnd_libglvnd_gl_LIB_DIRS_RELEASE}"
                              "${libglvnd_libglvnd_gl_BIN_DIRS_RELEASE}" # package_bindir
                              "${libglvnd_libglvnd_gl_LIBRARY_TYPE_RELEASE}"
                              "${libglvnd_libglvnd_gl_IS_HOST_WINDOWS_RELEASE}"
                              libglvnd_libglvnd_gl_DEPS_TARGET
                              libglvnd_libglvnd_gl_LIBRARIES_TARGETS
                              "_RELEASE"
                              "libglvnd_libglvnd_gl"
                              "${libglvnd_libglvnd_gl_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET libglvnd::gl
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gl_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gl_LIBRARIES_TARGETS}>
                     )

        if("${libglvnd_libglvnd_gl_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET libglvnd::gl
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         libglvnd_libglvnd_gl_DEPS_TARGET)
        endif()

        set_property(TARGET libglvnd::gl APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gl_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET libglvnd::gl APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gl_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::gl APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gl_LIB_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::gl APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gl_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET libglvnd::gl APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gl_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT libglvnd::gles2 #############

        set(libglvnd_libglvnd_gles2_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(libglvnd_libglvnd_gles2_FRAMEWORKS_FOUND_RELEASE "${libglvnd_libglvnd_gles2_FRAMEWORKS_RELEASE}" "${libglvnd_libglvnd_gles2_FRAMEWORK_DIRS_RELEASE}")

        set(libglvnd_libglvnd_gles2_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET libglvnd_libglvnd_gles2_DEPS_TARGET)
            add_library(libglvnd_libglvnd_gles2_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET libglvnd_libglvnd_gles2_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles2_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles2_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles2_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'libglvnd_libglvnd_gles2_DEPS_TARGET' to all of them
        conan_package_library_targets("${libglvnd_libglvnd_gles2_LIBS_RELEASE}"
                              "${libglvnd_libglvnd_gles2_LIB_DIRS_RELEASE}"
                              "${libglvnd_libglvnd_gles2_BIN_DIRS_RELEASE}" # package_bindir
                              "${libglvnd_libglvnd_gles2_LIBRARY_TYPE_RELEASE}"
                              "${libglvnd_libglvnd_gles2_IS_HOST_WINDOWS_RELEASE}"
                              libglvnd_libglvnd_gles2_DEPS_TARGET
                              libglvnd_libglvnd_gles2_LIBRARIES_TARGETS
                              "_RELEASE"
                              "libglvnd_libglvnd_gles2"
                              "${libglvnd_libglvnd_gles2_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET libglvnd::gles2
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles2_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles2_LIBRARIES_TARGETS}>
                     )

        if("${libglvnd_libglvnd_gles2_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET libglvnd::gles2
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         libglvnd_libglvnd_gles2_DEPS_TARGET)
        endif()

        set_property(TARGET libglvnd::gles2 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles2_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET libglvnd::gles2 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles2_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::gles2 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles2_LIB_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::gles2 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles2_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET libglvnd::gles2 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles2_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT libglvnd::gles1 #############

        set(libglvnd_libglvnd_gles1_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(libglvnd_libglvnd_gles1_FRAMEWORKS_FOUND_RELEASE "${libglvnd_libglvnd_gles1_FRAMEWORKS_RELEASE}" "${libglvnd_libglvnd_gles1_FRAMEWORK_DIRS_RELEASE}")

        set(libglvnd_libglvnd_gles1_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET libglvnd_libglvnd_gles1_DEPS_TARGET)
            add_library(libglvnd_libglvnd_gles1_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET libglvnd_libglvnd_gles1_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles1_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles1_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles1_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'libglvnd_libglvnd_gles1_DEPS_TARGET' to all of them
        conan_package_library_targets("${libglvnd_libglvnd_gles1_LIBS_RELEASE}"
                              "${libglvnd_libglvnd_gles1_LIB_DIRS_RELEASE}"
                              "${libglvnd_libglvnd_gles1_BIN_DIRS_RELEASE}" # package_bindir
                              "${libglvnd_libglvnd_gles1_LIBRARY_TYPE_RELEASE}"
                              "${libglvnd_libglvnd_gles1_IS_HOST_WINDOWS_RELEASE}"
                              libglvnd_libglvnd_gles1_DEPS_TARGET
                              libglvnd_libglvnd_gles1_LIBRARIES_TARGETS
                              "_RELEASE"
                              "libglvnd_libglvnd_gles1"
                              "${libglvnd_libglvnd_gles1_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET libglvnd::gles1
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles1_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles1_LIBRARIES_TARGETS}>
                     )

        if("${libglvnd_libglvnd_gles1_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET libglvnd::gles1
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         libglvnd_libglvnd_gles1_DEPS_TARGET)
        endif()

        set_property(TARGET libglvnd::gles1 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles1_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET libglvnd::gles1 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles1_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::gles1 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles1_LIB_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::gles1 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles1_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET libglvnd::gles1 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gles1_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT libglvnd::glx #############

        set(libglvnd_libglvnd_glx_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(libglvnd_libglvnd_glx_FRAMEWORKS_FOUND_RELEASE "${libglvnd_libglvnd_glx_FRAMEWORKS_RELEASE}" "${libglvnd_libglvnd_glx_FRAMEWORK_DIRS_RELEASE}")

        set(libglvnd_libglvnd_glx_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET libglvnd_libglvnd_glx_DEPS_TARGET)
            add_library(libglvnd_libglvnd_glx_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET libglvnd_libglvnd_glx_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_glx_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_glx_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_glx_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'libglvnd_libglvnd_glx_DEPS_TARGET' to all of them
        conan_package_library_targets("${libglvnd_libglvnd_glx_LIBS_RELEASE}"
                              "${libglvnd_libglvnd_glx_LIB_DIRS_RELEASE}"
                              "${libglvnd_libglvnd_glx_BIN_DIRS_RELEASE}" # package_bindir
                              "${libglvnd_libglvnd_glx_LIBRARY_TYPE_RELEASE}"
                              "${libglvnd_libglvnd_glx_IS_HOST_WINDOWS_RELEASE}"
                              libglvnd_libglvnd_glx_DEPS_TARGET
                              libglvnd_libglvnd_glx_LIBRARIES_TARGETS
                              "_RELEASE"
                              "libglvnd_libglvnd_glx"
                              "${libglvnd_libglvnd_glx_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET libglvnd::glx
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_glx_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_glx_LIBRARIES_TARGETS}>
                     )

        if("${libglvnd_libglvnd_glx_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET libglvnd::glx
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         libglvnd_libglvnd_glx_DEPS_TARGET)
        endif()

        set_property(TARGET libglvnd::glx APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_glx_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET libglvnd::glx APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_glx_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::glx APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_glx_LIB_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::glx APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_glx_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET libglvnd::glx APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_glx_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT libglvnd::egl #############

        set(libglvnd_libglvnd_egl_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(libglvnd_libglvnd_egl_FRAMEWORKS_FOUND_RELEASE "${libglvnd_libglvnd_egl_FRAMEWORKS_RELEASE}" "${libglvnd_libglvnd_egl_FRAMEWORK_DIRS_RELEASE}")

        set(libglvnd_libglvnd_egl_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET libglvnd_libglvnd_egl_DEPS_TARGET)
            add_library(libglvnd_libglvnd_egl_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET libglvnd_libglvnd_egl_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_egl_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_egl_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_egl_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'libglvnd_libglvnd_egl_DEPS_TARGET' to all of them
        conan_package_library_targets("${libglvnd_libglvnd_egl_LIBS_RELEASE}"
                              "${libglvnd_libglvnd_egl_LIB_DIRS_RELEASE}"
                              "${libglvnd_libglvnd_egl_BIN_DIRS_RELEASE}" # package_bindir
                              "${libglvnd_libglvnd_egl_LIBRARY_TYPE_RELEASE}"
                              "${libglvnd_libglvnd_egl_IS_HOST_WINDOWS_RELEASE}"
                              libglvnd_libglvnd_egl_DEPS_TARGET
                              libglvnd_libglvnd_egl_LIBRARIES_TARGETS
                              "_RELEASE"
                              "libglvnd_libglvnd_egl"
                              "${libglvnd_libglvnd_egl_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET libglvnd::egl
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_egl_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_egl_LIBRARIES_TARGETS}>
                     )

        if("${libglvnd_libglvnd_egl_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET libglvnd::egl
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         libglvnd_libglvnd_egl_DEPS_TARGET)
        endif()

        set_property(TARGET libglvnd::egl APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_egl_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET libglvnd::egl APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_egl_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::egl APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_egl_LIB_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::egl APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_egl_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET libglvnd::egl APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_egl_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT libglvnd::opengl #############

        set(libglvnd_libglvnd_opengl_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(libglvnd_libglvnd_opengl_FRAMEWORKS_FOUND_RELEASE "${libglvnd_libglvnd_opengl_FRAMEWORKS_RELEASE}" "${libglvnd_libglvnd_opengl_FRAMEWORK_DIRS_RELEASE}")

        set(libglvnd_libglvnd_opengl_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET libglvnd_libglvnd_opengl_DEPS_TARGET)
            add_library(libglvnd_libglvnd_opengl_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET libglvnd_libglvnd_opengl_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_opengl_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_opengl_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_opengl_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'libglvnd_libglvnd_opengl_DEPS_TARGET' to all of them
        conan_package_library_targets("${libglvnd_libglvnd_opengl_LIBS_RELEASE}"
                              "${libglvnd_libglvnd_opengl_LIB_DIRS_RELEASE}"
                              "${libglvnd_libglvnd_opengl_BIN_DIRS_RELEASE}" # package_bindir
                              "${libglvnd_libglvnd_opengl_LIBRARY_TYPE_RELEASE}"
                              "${libglvnd_libglvnd_opengl_IS_HOST_WINDOWS_RELEASE}"
                              libglvnd_libglvnd_opengl_DEPS_TARGET
                              libglvnd_libglvnd_opengl_LIBRARIES_TARGETS
                              "_RELEASE"
                              "libglvnd_libglvnd_opengl"
                              "${libglvnd_libglvnd_opengl_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET libglvnd::opengl
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_opengl_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_opengl_LIBRARIES_TARGETS}>
                     )

        if("${libglvnd_libglvnd_opengl_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET libglvnd::opengl
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         libglvnd_libglvnd_opengl_DEPS_TARGET)
        endif()

        set_property(TARGET libglvnd::opengl APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_opengl_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET libglvnd::opengl APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_opengl_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::opengl APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_opengl_LIB_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::opengl APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_opengl_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET libglvnd::opengl APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_opengl_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT libglvnd::gldispatch #############

        set(libglvnd_libglvnd_gldispatch_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(libglvnd_libglvnd_gldispatch_FRAMEWORKS_FOUND_RELEASE "${libglvnd_libglvnd_gldispatch_FRAMEWORKS_RELEASE}" "${libglvnd_libglvnd_gldispatch_FRAMEWORK_DIRS_RELEASE}")

        set(libglvnd_libglvnd_gldispatch_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET libglvnd_libglvnd_gldispatch_DEPS_TARGET)
            add_library(libglvnd_libglvnd_gldispatch_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET libglvnd_libglvnd_gldispatch_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gldispatch_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gldispatch_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gldispatch_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'libglvnd_libglvnd_gldispatch_DEPS_TARGET' to all of them
        conan_package_library_targets("${libglvnd_libglvnd_gldispatch_LIBS_RELEASE}"
                              "${libglvnd_libglvnd_gldispatch_LIB_DIRS_RELEASE}"
                              "${libglvnd_libglvnd_gldispatch_BIN_DIRS_RELEASE}" # package_bindir
                              "${libglvnd_libglvnd_gldispatch_LIBRARY_TYPE_RELEASE}"
                              "${libglvnd_libglvnd_gldispatch_IS_HOST_WINDOWS_RELEASE}"
                              libglvnd_libglvnd_gldispatch_DEPS_TARGET
                              libglvnd_libglvnd_gldispatch_LIBRARIES_TARGETS
                              "_RELEASE"
                              "libglvnd_libglvnd_gldispatch"
                              "${libglvnd_libglvnd_gldispatch_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET libglvnd::gldispatch
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gldispatch_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gldispatch_LIBRARIES_TARGETS}>
                     )

        if("${libglvnd_libglvnd_gldispatch_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET libglvnd::gldispatch
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         libglvnd_libglvnd_gldispatch_DEPS_TARGET)
        endif()

        set_property(TARGET libglvnd::gldispatch APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gldispatch_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET libglvnd::gldispatch APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gldispatch_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::gldispatch APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gldispatch_LIB_DIRS_RELEASE}>)
        set_property(TARGET libglvnd::gldispatch APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gldispatch_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET libglvnd::gldispatch APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${libglvnd_libglvnd_gldispatch_COMPILE_OPTIONS_RELEASE}>)


    ########## AGGREGATED GLOBAL TARGET WITH THE COMPONENTS #####################
    set_property(TARGET libglvnd::libglvnd APPEND PROPERTY INTERFACE_LINK_LIBRARIES libglvnd::gl)
    set_property(TARGET libglvnd::libglvnd APPEND PROPERTY INTERFACE_LINK_LIBRARIES libglvnd::gles2)
    set_property(TARGET libglvnd::libglvnd APPEND PROPERTY INTERFACE_LINK_LIBRARIES libglvnd::gles1)
    set_property(TARGET libglvnd::libglvnd APPEND PROPERTY INTERFACE_LINK_LIBRARIES libglvnd::glx)
    set_property(TARGET libglvnd::libglvnd APPEND PROPERTY INTERFACE_LINK_LIBRARIES libglvnd::egl)
    set_property(TARGET libglvnd::libglvnd APPEND PROPERTY INTERFACE_LINK_LIBRARIES libglvnd::opengl)
    set_property(TARGET libglvnd::libglvnd APPEND PROPERTY INTERFACE_LINK_LIBRARIES libglvnd::gldispatch)

########## For the modules (FindXXX)
set(libglvnd_LIBRARIES_RELEASE libglvnd::libglvnd)
