# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(glew_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(glew_FRAMEWORKS_FOUND_RELEASE "${glew_FRAMEWORKS_RELEASE}" "${glew_FRAMEWORK_DIRS_RELEASE}")

set(glew_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET glew_DEPS_TARGET)
    add_library(glew_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET glew_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${glew_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${glew_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:opengl::opengl;mesa-glu::mesa-glu>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### glew_DEPS_TARGET to all of them
conan_package_library_targets("${glew_LIBS_RELEASE}"    # libraries
                              "${glew_LIB_DIRS_RELEASE}" # package_libdir
                              "${glew_BIN_DIRS_RELEASE}" # package_bindir
                              "${glew_LIBRARY_TYPE_RELEASE}"
                              "${glew_IS_HOST_WINDOWS_RELEASE}"
                              glew_DEPS_TARGET
                              glew_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "glew"    # package_name
                              "${glew_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${glew_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## COMPONENTS TARGET PROPERTIES Release ########################################

    ########## COMPONENT GLEW::GLEW #############

        set(glew_GLEW_GLEW_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(glew_GLEW_GLEW_FRAMEWORKS_FOUND_RELEASE "${glew_GLEW_GLEW_FRAMEWORKS_RELEASE}" "${glew_GLEW_GLEW_FRAMEWORK_DIRS_RELEASE}")

        set(glew_GLEW_GLEW_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET glew_GLEW_GLEW_DEPS_TARGET)
            add_library(glew_GLEW_GLEW_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET glew_GLEW_GLEW_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${glew_GLEW_GLEW_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${glew_GLEW_GLEW_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${glew_GLEW_GLEW_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'glew_GLEW_GLEW_DEPS_TARGET' to all of them
        conan_package_library_targets("${glew_GLEW_GLEW_LIBS_RELEASE}"
                              "${glew_GLEW_GLEW_LIB_DIRS_RELEASE}"
                              "${glew_GLEW_GLEW_BIN_DIRS_RELEASE}" # package_bindir
                              "${glew_GLEW_GLEW_LIBRARY_TYPE_RELEASE}"
                              "${glew_GLEW_GLEW_IS_HOST_WINDOWS_RELEASE}"
                              glew_GLEW_GLEW_DEPS_TARGET
                              glew_GLEW_GLEW_LIBRARIES_TARGETS
                              "_RELEASE"
                              "glew_GLEW_GLEW"
                              "${glew_GLEW_GLEW_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET GLEW::GLEW
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${glew_GLEW_GLEW_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${glew_GLEW_GLEW_LIBRARIES_TARGETS}>
                     )

        if("${glew_GLEW_GLEW_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET GLEW::GLEW
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         glew_GLEW_GLEW_DEPS_TARGET)
        endif()

        set_property(TARGET GLEW::GLEW APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${glew_GLEW_GLEW_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET GLEW::GLEW APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${glew_GLEW_GLEW_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET GLEW::GLEW APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${glew_GLEW_GLEW_LIB_DIRS_RELEASE}>)
        set_property(TARGET GLEW::GLEW APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${glew_GLEW_GLEW_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET GLEW::GLEW APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${glew_GLEW_GLEW_COMPILE_OPTIONS_RELEASE}>)


    ########## AGGREGATED GLOBAL TARGET WITH THE COMPONENTS #####################
    set_property(TARGET GLEW::GLEW APPEND PROPERTY INTERFACE_LINK_LIBRARIES GLEW::GLEW)

########## For the modules (FindXXX)
set(glew_LIBRARIES_RELEASE GLEW::GLEW)
