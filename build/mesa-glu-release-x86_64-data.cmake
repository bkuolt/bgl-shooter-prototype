########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(mesa-glu_COMPONENT_NAMES "")
if(DEFINED mesa-glu_FIND_DEPENDENCY_NAMES)
  list(APPEND mesa-glu_FIND_DEPENDENCY_NAMES libglvnd)
  list(REMOVE_DUPLICATES mesa-glu_FIND_DEPENDENCY_NAMES)
else()
  set(mesa-glu_FIND_DEPENDENCY_NAMES libglvnd)
endif()
set(libglvnd_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(mesa-glu_PACKAGE_FOLDER_RELEASE "/home/bastian/.conan2/p/b/mesa-dad2e7a0d1fa4/p")
set(mesa-glu_BUILD_MODULES_PATHS_RELEASE )


set(mesa-glu_INCLUDE_DIRS_RELEASE "${mesa-glu_PACKAGE_FOLDER_RELEASE}/include")
set(mesa-glu_RES_DIRS_RELEASE )
set(mesa-glu_DEFINITIONS_RELEASE )
set(mesa-glu_SHARED_LINK_FLAGS_RELEASE )
set(mesa-glu_EXE_LINK_FLAGS_RELEASE )
set(mesa-glu_OBJECTS_RELEASE )
set(mesa-glu_COMPILE_DEFINITIONS_RELEASE )
set(mesa-glu_COMPILE_OPTIONS_C_RELEASE )
set(mesa-glu_COMPILE_OPTIONS_CXX_RELEASE )
set(mesa-glu_LIB_DIRS_RELEASE "${mesa-glu_PACKAGE_FOLDER_RELEASE}/lib")
set(mesa-glu_BIN_DIRS_RELEASE )
set(mesa-glu_LIBRARY_TYPE_RELEASE STATIC)
set(mesa-glu_IS_HOST_WINDOWS_RELEASE 0)
set(mesa-glu_LIBS_RELEASE GLU)
set(mesa-glu_SYSTEM_LIBS_RELEASE )
set(mesa-glu_FRAMEWORK_DIRS_RELEASE )
set(mesa-glu_FRAMEWORKS_RELEASE )
set(mesa-glu_BUILD_DIRS_RELEASE )
set(mesa-glu_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(mesa-glu_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${mesa-glu_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${mesa-glu_COMPILE_OPTIONS_C_RELEASE}>")
set(mesa-glu_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${mesa-glu_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${mesa-glu_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${mesa-glu_EXE_LINK_FLAGS_RELEASE}>")


set(mesa-glu_COMPONENTS_RELEASE )