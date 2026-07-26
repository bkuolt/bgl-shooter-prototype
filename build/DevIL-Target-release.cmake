# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(devil_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(devil_FRAMEWORKS_FOUND_RELEASE "${devil_FRAMEWORKS_RELEASE}" "${devil_FRAMEWORK_DIRS_RELEASE}")

set(devil_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET devil_DEPS_TARGET)
    add_library(devil_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET devil_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${devil_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${devil_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:PNG::PNG;JPEG::JPEG;TIFF::TIFF;Jasper::Jasper;libsquish::libsquish;lcms::lcms>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### devil_DEPS_TARGET to all of them
conan_package_library_targets("${devil_LIBS_RELEASE}"    # libraries
                              "${devil_LIB_DIRS_RELEASE}" # package_libdir
                              "${devil_BIN_DIRS_RELEASE}" # package_bindir
                              "${devil_LIBRARY_TYPE_RELEASE}"
                              "${devil_IS_HOST_WINDOWS_RELEASE}"
                              devil_DEPS_TARGET
                              devil_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "devil"    # package_name
                              "${devil_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${devil_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## COMPONENTS TARGET PROPERTIES Release ########################################

    ########## COMPONENT DevIL::ILUT #############

        set(devil_DevIL_ILUT_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(devil_DevIL_ILUT_FRAMEWORKS_FOUND_RELEASE "${devil_DevIL_ILUT_FRAMEWORKS_RELEASE}" "${devil_DevIL_ILUT_FRAMEWORK_DIRS_RELEASE}")

        set(devil_DevIL_ILUT_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET devil_DevIL_ILUT_DEPS_TARGET)
            add_library(devil_DevIL_ILUT_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET devil_DevIL_ILUT_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${devil_DevIL_ILUT_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${devil_DevIL_ILUT_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${devil_DevIL_ILUT_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'devil_DevIL_ILUT_DEPS_TARGET' to all of them
        conan_package_library_targets("${devil_DevIL_ILUT_LIBS_RELEASE}"
                              "${devil_DevIL_ILUT_LIB_DIRS_RELEASE}"
                              "${devil_DevIL_ILUT_BIN_DIRS_RELEASE}" # package_bindir
                              "${devil_DevIL_ILUT_LIBRARY_TYPE_RELEASE}"
                              "${devil_DevIL_ILUT_IS_HOST_WINDOWS_RELEASE}"
                              devil_DevIL_ILUT_DEPS_TARGET
                              devil_DevIL_ILUT_LIBRARIES_TARGETS
                              "_RELEASE"
                              "devil_DevIL_ILUT"
                              "${devil_DevIL_ILUT_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET DevIL::ILUT
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${devil_DevIL_ILUT_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${devil_DevIL_ILUT_LIBRARIES_TARGETS}>
                     )

        if("${devil_DevIL_ILUT_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET DevIL::ILUT
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         devil_DevIL_ILUT_DEPS_TARGET)
        endif()

        set_property(TARGET DevIL::ILUT APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${devil_DevIL_ILUT_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET DevIL::ILUT APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${devil_DevIL_ILUT_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET DevIL::ILUT APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${devil_DevIL_ILUT_LIB_DIRS_RELEASE}>)
        set_property(TARGET DevIL::ILUT APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${devil_DevIL_ILUT_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET DevIL::ILUT APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${devil_DevIL_ILUT_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT DevIL::ILU #############

        set(devil_DevIL_ILU_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(devil_DevIL_ILU_FRAMEWORKS_FOUND_RELEASE "${devil_DevIL_ILU_FRAMEWORKS_RELEASE}" "${devil_DevIL_ILU_FRAMEWORK_DIRS_RELEASE}")

        set(devil_DevIL_ILU_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET devil_DevIL_ILU_DEPS_TARGET)
            add_library(devil_DevIL_ILU_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET devil_DevIL_ILU_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${devil_DevIL_ILU_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${devil_DevIL_ILU_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${devil_DevIL_ILU_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'devil_DevIL_ILU_DEPS_TARGET' to all of them
        conan_package_library_targets("${devil_DevIL_ILU_LIBS_RELEASE}"
                              "${devil_DevIL_ILU_LIB_DIRS_RELEASE}"
                              "${devil_DevIL_ILU_BIN_DIRS_RELEASE}" # package_bindir
                              "${devil_DevIL_ILU_LIBRARY_TYPE_RELEASE}"
                              "${devil_DevIL_ILU_IS_HOST_WINDOWS_RELEASE}"
                              devil_DevIL_ILU_DEPS_TARGET
                              devil_DevIL_ILU_LIBRARIES_TARGETS
                              "_RELEASE"
                              "devil_DevIL_ILU"
                              "${devil_DevIL_ILU_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET DevIL::ILU
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${devil_DevIL_ILU_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${devil_DevIL_ILU_LIBRARIES_TARGETS}>
                     )

        if("${devil_DevIL_ILU_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET DevIL::ILU
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         devil_DevIL_ILU_DEPS_TARGET)
        endif()

        set_property(TARGET DevIL::ILU APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${devil_DevIL_ILU_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET DevIL::ILU APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${devil_DevIL_ILU_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET DevIL::ILU APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${devil_DevIL_ILU_LIB_DIRS_RELEASE}>)
        set_property(TARGET DevIL::ILU APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${devil_DevIL_ILU_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET DevIL::ILU APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${devil_DevIL_ILU_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT DevIL::IL #############

        set(devil_DevIL_IL_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(devil_DevIL_IL_FRAMEWORKS_FOUND_RELEASE "${devil_DevIL_IL_FRAMEWORKS_RELEASE}" "${devil_DevIL_IL_FRAMEWORK_DIRS_RELEASE}")

        set(devil_DevIL_IL_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET devil_DevIL_IL_DEPS_TARGET)
            add_library(devil_DevIL_IL_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET devil_DevIL_IL_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${devil_DevIL_IL_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${devil_DevIL_IL_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${devil_DevIL_IL_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'devil_DevIL_IL_DEPS_TARGET' to all of them
        conan_package_library_targets("${devil_DevIL_IL_LIBS_RELEASE}"
                              "${devil_DevIL_IL_LIB_DIRS_RELEASE}"
                              "${devil_DevIL_IL_BIN_DIRS_RELEASE}" # package_bindir
                              "${devil_DevIL_IL_LIBRARY_TYPE_RELEASE}"
                              "${devil_DevIL_IL_IS_HOST_WINDOWS_RELEASE}"
                              devil_DevIL_IL_DEPS_TARGET
                              devil_DevIL_IL_LIBRARIES_TARGETS
                              "_RELEASE"
                              "devil_DevIL_IL"
                              "${devil_DevIL_IL_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET DevIL::IL
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${devil_DevIL_IL_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${devil_DevIL_IL_LIBRARIES_TARGETS}>
                     )

        if("${devil_DevIL_IL_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET DevIL::IL
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         devil_DevIL_IL_DEPS_TARGET)
        endif()

        set_property(TARGET DevIL::IL APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${devil_DevIL_IL_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET DevIL::IL APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${devil_DevIL_IL_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET DevIL::IL APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${devil_DevIL_IL_LIB_DIRS_RELEASE}>)
        set_property(TARGET DevIL::IL APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${devil_DevIL_IL_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET DevIL::IL APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${devil_DevIL_IL_COMPILE_OPTIONS_RELEASE}>)


    ########## AGGREGATED GLOBAL TARGET WITH THE COMPONENTS #####################
    set_property(TARGET DevIL::DevIL APPEND PROPERTY INTERFACE_LINK_LIBRARIES DevIL::ILUT)
    set_property(TARGET DevIL::DevIL APPEND PROPERTY INTERFACE_LINK_LIBRARIES DevIL::ILU)
    set_property(TARGET DevIL::DevIL APPEND PROPERTY INTERFACE_LINK_LIBRARIES DevIL::IL)

########## For the modules (FindXXX)
set(devil_LIBRARIES_RELEASE DevIL::DevIL)
