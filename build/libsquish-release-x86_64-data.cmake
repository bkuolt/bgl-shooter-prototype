########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(libsquish_COMPONENT_NAMES "")
if(DEFINED libsquish_FIND_DEPENDENCY_NAMES)
  list(APPEND libsquish_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES libsquish_FIND_DEPENDENCY_NAMES)
else()
  set(libsquish_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(libsquish_PACKAGE_FOLDER_RELEASE "/home/bastian/.conan2/p/b/libsqec9ecfc5dc463/p")
set(libsquish_BUILD_MODULES_PATHS_RELEASE )


set(libsquish_INCLUDE_DIRS_RELEASE )
set(libsquish_RES_DIRS_RELEASE )
set(libsquish_DEFINITIONS_RELEASE )
set(libsquish_SHARED_LINK_FLAGS_RELEASE )
set(libsquish_EXE_LINK_FLAGS_RELEASE )
set(libsquish_OBJECTS_RELEASE )
set(libsquish_COMPILE_DEFINITIONS_RELEASE )
set(libsquish_COMPILE_OPTIONS_C_RELEASE )
set(libsquish_COMPILE_OPTIONS_CXX_RELEASE )
set(libsquish_LIB_DIRS_RELEASE "${libsquish_PACKAGE_FOLDER_RELEASE}/lib")
set(libsquish_BIN_DIRS_RELEASE )
set(libsquish_LIBRARY_TYPE_RELEASE STATIC)
set(libsquish_IS_HOST_WINDOWS_RELEASE 0)
set(libsquish_LIBS_RELEASE squish)
set(libsquish_SYSTEM_LIBS_RELEASE m)
set(libsquish_FRAMEWORK_DIRS_RELEASE )
set(libsquish_FRAMEWORKS_RELEASE )
set(libsquish_BUILD_DIRS_RELEASE )
set(libsquish_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(libsquish_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libsquish_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libsquish_COMPILE_OPTIONS_C_RELEASE}>")
set(libsquish_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libsquish_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libsquish_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libsquish_EXE_LINK_FLAGS_RELEASE}>")


set(libsquish_COMPONENTS_RELEASE )