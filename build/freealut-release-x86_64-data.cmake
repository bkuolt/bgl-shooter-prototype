########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(freealut_COMPONENT_NAMES "")
if(DEFINED freealut_FIND_DEPENDENCY_NAMES)
  list(APPEND freealut_FIND_DEPENDENCY_NAMES OpenAL)
  list(REMOVE_DUPLICATES freealut_FIND_DEPENDENCY_NAMES)
else()
  set(freealut_FIND_DEPENDENCY_NAMES OpenAL)
endif()
set(OpenAL_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(freealut_PACKAGE_FOLDER_RELEASE "/home/bastian/.conan2/p/b/freea4ded24f86f55c/p")
set(freealut_BUILD_MODULES_PATHS_RELEASE )


set(freealut_INCLUDE_DIRS_RELEASE "${freealut_PACKAGE_FOLDER_RELEASE}/include")
set(freealut_RES_DIRS_RELEASE )
set(freealut_DEFINITIONS_RELEASE )
set(freealut_SHARED_LINK_FLAGS_RELEASE )
set(freealut_EXE_LINK_FLAGS_RELEASE )
set(freealut_OBJECTS_RELEASE )
set(freealut_COMPILE_DEFINITIONS_RELEASE )
set(freealut_COMPILE_OPTIONS_C_RELEASE )
set(freealut_COMPILE_OPTIONS_CXX_RELEASE )
set(freealut_LIB_DIRS_RELEASE "${freealut_PACKAGE_FOLDER_RELEASE}/lib")
set(freealut_BIN_DIRS_RELEASE )
set(freealut_LIBRARY_TYPE_RELEASE STATIC)
set(freealut_IS_HOST_WINDOWS_RELEASE 0)
set(freealut_LIBS_RELEASE alut)
set(freealut_SYSTEM_LIBS_RELEASE m pthread)
set(freealut_FRAMEWORK_DIRS_RELEASE )
set(freealut_FRAMEWORKS_RELEASE )
set(freealut_BUILD_DIRS_RELEASE )
set(freealut_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(freealut_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${freealut_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${freealut_COMPILE_OPTIONS_C_RELEASE}>")
set(freealut_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${freealut_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${freealut_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${freealut_EXE_LINK_FLAGS_RELEASE}>")


set(freealut_COMPONENTS_RELEASE )