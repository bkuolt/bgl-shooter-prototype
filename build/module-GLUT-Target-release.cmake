# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(freeglut_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(freeglut_FRAMEWORKS_FOUND_RELEASE "${freeglut_FRAMEWORKS_RELEASE}" "${freeglut_FRAMEWORK_DIRS_RELEASE}")

set(freeglut_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET freeglut_DEPS_TARGET)
    add_library(freeglut_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET freeglut_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${freeglut_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${freeglut_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:libglvnd::gl;libglvnd::opengl;xorg::xorg;mesa-glu::mesa-glu>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### freeglut_DEPS_TARGET to all of them
conan_package_library_targets("${freeglut_LIBS_RELEASE}"    # libraries
                              "${freeglut_LIB_DIRS_RELEASE}" # package_libdir
                              "${freeglut_BIN_DIRS_RELEASE}" # package_bindir
                              "${freeglut_LIBRARY_TYPE_RELEASE}"
                              "${freeglut_IS_HOST_WINDOWS_RELEASE}"
                              freeglut_DEPS_TARGET
                              freeglut_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "freeglut"    # package_name
                              "${freeglut_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${freeglut_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## COMPONENTS TARGET PROPERTIES Release ########################################

    ########## COMPONENT GLUT::GLUT #############

        set(freeglut_GLUT_GLUT_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(freeglut_GLUT_GLUT_FRAMEWORKS_FOUND_RELEASE "${freeglut_GLUT_GLUT_FRAMEWORKS_RELEASE}" "${freeglut_GLUT_GLUT_FRAMEWORK_DIRS_RELEASE}")

        set(freeglut_GLUT_GLUT_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET freeglut_GLUT_GLUT_DEPS_TARGET)
            add_library(freeglut_GLUT_GLUT_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET freeglut_GLUT_GLUT_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${freeglut_GLUT_GLUT_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${freeglut_GLUT_GLUT_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${freeglut_GLUT_GLUT_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'freeglut_GLUT_GLUT_DEPS_TARGET' to all of them
        conan_package_library_targets("${freeglut_GLUT_GLUT_LIBS_RELEASE}"
                              "${freeglut_GLUT_GLUT_LIB_DIRS_RELEASE}"
                              "${freeglut_GLUT_GLUT_BIN_DIRS_RELEASE}" # package_bindir
                              "${freeglut_GLUT_GLUT_LIBRARY_TYPE_RELEASE}"
                              "${freeglut_GLUT_GLUT_IS_HOST_WINDOWS_RELEASE}"
                              freeglut_GLUT_GLUT_DEPS_TARGET
                              freeglut_GLUT_GLUT_LIBRARIES_TARGETS
                              "_RELEASE"
                              "freeglut_GLUT_GLUT"
                              "${freeglut_GLUT_GLUT_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET GLUT::GLUT
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${freeglut_GLUT_GLUT_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${freeglut_GLUT_GLUT_LIBRARIES_TARGETS}>
                     )

        if("${freeglut_GLUT_GLUT_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET GLUT::GLUT
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         freeglut_GLUT_GLUT_DEPS_TARGET)
        endif()

        set_property(TARGET GLUT::GLUT APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${freeglut_GLUT_GLUT_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET GLUT::GLUT APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${freeglut_GLUT_GLUT_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET GLUT::GLUT APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${freeglut_GLUT_GLUT_LIB_DIRS_RELEASE}>)
        set_property(TARGET GLUT::GLUT APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${freeglut_GLUT_GLUT_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET GLUT::GLUT APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${freeglut_GLUT_GLUT_COMPILE_OPTIONS_RELEASE}>)


    ########## AGGREGATED GLOBAL TARGET WITH THE COMPONENTS #####################
    set_property(TARGET GLUT::GLUT APPEND PROPERTY INTERFACE_LINK_LIBRARIES GLUT::GLUT)

########## For the modules (FindXXX)
set(freeglut_LIBRARIES_RELEASE GLUT::GLUT)
