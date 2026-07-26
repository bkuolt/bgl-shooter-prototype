########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(jasper_COMPONENT_NAMES "")
if(DEFINED jasper_FIND_DEPENDENCY_NAMES)
  list(APPEND jasper_FIND_DEPENDENCY_NAMES JPEG)
  list(REMOVE_DUPLICATES jasper_FIND_DEPENDENCY_NAMES)
else()
  set(jasper_FIND_DEPENDENCY_NAMES JPEG)
endif()
set(JPEG_FIND_MODE "MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(jasper_PACKAGE_FOLDER_RELEASE "/home/bastian/.conan2/p/b/jaspee9ea4d4426b03/p")
set(jasper_BUILD_MODULES_PATHS_RELEASE "${jasper_PACKAGE_FOLDER_RELEASE}/lib/cmake/conan-official-jasper-variables.cmake")


set(jasper_INCLUDE_DIRS_RELEASE )
set(jasper_RES_DIRS_RELEASE )
set(jasper_DEFINITIONS_RELEASE )
set(jasper_SHARED_LINK_FLAGS_RELEASE )
set(jasper_EXE_LINK_FLAGS_RELEASE )
set(jasper_OBJECTS_RELEASE )
set(jasper_COMPILE_DEFINITIONS_RELEASE )
set(jasper_COMPILE_OPTIONS_C_RELEASE )
set(jasper_COMPILE_OPTIONS_CXX_RELEASE )
set(jasper_LIB_DIRS_RELEASE "${jasper_PACKAGE_FOLDER_RELEASE}/lib")
set(jasper_BIN_DIRS_RELEASE )
set(jasper_LIBRARY_TYPE_RELEASE STATIC)
set(jasper_IS_HOST_WINDOWS_RELEASE 0)
set(jasper_LIBS_RELEASE jasper)
set(jasper_SYSTEM_LIBS_RELEASE m pthread)
set(jasper_FRAMEWORK_DIRS_RELEASE )
set(jasper_FRAMEWORKS_RELEASE )
set(jasper_BUILD_DIRS_RELEASE )
set(jasper_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(jasper_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${jasper_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${jasper_COMPILE_OPTIONS_C_RELEASE}>")
set(jasper_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${jasper_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${jasper_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${jasper_EXE_LINK_FLAGS_RELEASE}>")


set(jasper_COMPONENTS_RELEASE )