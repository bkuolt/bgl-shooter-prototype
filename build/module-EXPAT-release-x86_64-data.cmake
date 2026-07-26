########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(expat_COMPONENT_NAMES "")
if(DEFINED expat_FIND_DEPENDENCY_NAMES)
  list(APPEND expat_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES expat_FIND_DEPENDENCY_NAMES)
else()
  set(expat_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(expat_PACKAGE_FOLDER_RELEASE "/home/bastian/.conan2/p/b/expat6bc99f57b338a/p")
set(expat_BUILD_MODULES_PATHS_RELEASE )


set(expat_INCLUDE_DIRS_RELEASE )
set(expat_RES_DIRS_RELEASE )
set(expat_DEFINITIONS_RELEASE "-DXML_STATIC")
set(expat_SHARED_LINK_FLAGS_RELEASE )
set(expat_EXE_LINK_FLAGS_RELEASE )
set(expat_OBJECTS_RELEASE )
set(expat_COMPILE_DEFINITIONS_RELEASE "XML_STATIC")
set(expat_COMPILE_OPTIONS_C_RELEASE )
set(expat_COMPILE_OPTIONS_CXX_RELEASE )
set(expat_LIB_DIRS_RELEASE "${expat_PACKAGE_FOLDER_RELEASE}/lib")
set(expat_BIN_DIRS_RELEASE )
set(expat_LIBRARY_TYPE_RELEASE STATIC)
set(expat_IS_HOST_WINDOWS_RELEASE 0)
set(expat_LIBS_RELEASE expat)
set(expat_SYSTEM_LIBS_RELEASE m)
set(expat_FRAMEWORK_DIRS_RELEASE )
set(expat_FRAMEWORKS_RELEASE )
set(expat_BUILD_DIRS_RELEASE )
set(expat_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(expat_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${expat_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${expat_COMPILE_OPTIONS_C_RELEASE}>")
set(expat_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${expat_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${expat_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${expat_EXE_LINK_FLAGS_RELEASE}>")


set(expat_COMPONENTS_RELEASE )