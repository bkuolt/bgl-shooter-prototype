########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(lcms_COMPONENT_NAMES "")
if(DEFINED lcms_FIND_DEPENDENCY_NAMES)
  list(APPEND lcms_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES lcms_FIND_DEPENDENCY_NAMES)
else()
  set(lcms_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(lcms_PACKAGE_FOLDER_RELEASE "/home/bastian/.conan2/p/b/lcms3c46da213076d/p")
set(lcms_BUILD_MODULES_PATHS_RELEASE )


set(lcms_INCLUDE_DIRS_RELEASE )
set(lcms_RES_DIRS_RELEASE )
set(lcms_DEFINITIONS_RELEASE )
set(lcms_SHARED_LINK_FLAGS_RELEASE )
set(lcms_EXE_LINK_FLAGS_RELEASE )
set(lcms_OBJECTS_RELEASE )
set(lcms_COMPILE_DEFINITIONS_RELEASE )
set(lcms_COMPILE_OPTIONS_C_RELEASE )
set(lcms_COMPILE_OPTIONS_CXX_RELEASE )
set(lcms_LIB_DIRS_RELEASE "${lcms_PACKAGE_FOLDER_RELEASE}/lib")
set(lcms_BIN_DIRS_RELEASE )
set(lcms_LIBRARY_TYPE_RELEASE STATIC)
set(lcms_IS_HOST_WINDOWS_RELEASE 0)
set(lcms_LIBS_RELEASE lcms2)
set(lcms_SYSTEM_LIBS_RELEASE m pthread)
set(lcms_FRAMEWORK_DIRS_RELEASE )
set(lcms_FRAMEWORKS_RELEASE )
set(lcms_BUILD_DIRS_RELEASE )
set(lcms_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(lcms_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${lcms_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${lcms_COMPILE_OPTIONS_C_RELEASE}>")
set(lcms_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${lcms_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${lcms_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${lcms_EXE_LINK_FLAGS_RELEASE}>")


set(lcms_COMPONENTS_RELEASE )