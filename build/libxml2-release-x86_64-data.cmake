########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(libxml2_COMPONENT_NAMES "")
if(DEFINED libxml2_FIND_DEPENDENCY_NAMES)
  list(APPEND libxml2_FIND_DEPENDENCY_NAMES Iconv ZLIB)
  list(REMOVE_DUPLICATES libxml2_FIND_DEPENDENCY_NAMES)
else()
  set(libxml2_FIND_DEPENDENCY_NAMES Iconv ZLIB)
endif()
set(Iconv_FIND_MODE "NO_MODULE")
set(ZLIB_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(libxml2_PACKAGE_FOLDER_RELEASE "/home/bastian/.conan2/p/b/libxm287891207936a/p")
set(libxml2_BUILD_MODULES_PATHS_RELEASE )


set(libxml2_INCLUDE_DIRS_RELEASE )
set(libxml2_RES_DIRS_RELEASE )
set(libxml2_DEFINITIONS_RELEASE "-DLIBXML_STATIC")
set(libxml2_SHARED_LINK_FLAGS_RELEASE )
set(libxml2_EXE_LINK_FLAGS_RELEASE )
set(libxml2_OBJECTS_RELEASE )
set(libxml2_COMPILE_DEFINITIONS_RELEASE "LIBXML_STATIC")
set(libxml2_COMPILE_OPTIONS_C_RELEASE )
set(libxml2_COMPILE_OPTIONS_CXX_RELEASE )
set(libxml2_LIB_DIRS_RELEASE "${libxml2_PACKAGE_FOLDER_RELEASE}/lib")
set(libxml2_BIN_DIRS_RELEASE )
set(libxml2_LIBRARY_TYPE_RELEASE STATIC)
set(libxml2_IS_HOST_WINDOWS_RELEASE 0)
set(libxml2_LIBS_RELEASE xml2)
set(libxml2_SYSTEM_LIBS_RELEASE m dl pthread)
set(libxml2_FRAMEWORK_DIRS_RELEASE )
set(libxml2_FRAMEWORKS_RELEASE )
set(libxml2_BUILD_DIRS_RELEASE )
set(libxml2_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(libxml2_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libxml2_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libxml2_COMPILE_OPTIONS_C_RELEASE}>")
set(libxml2_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libxml2_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libxml2_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libxml2_EXE_LINK_FLAGS_RELEASE}>")


set(libxml2_COMPONENTS_RELEASE )