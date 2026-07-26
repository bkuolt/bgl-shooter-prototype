########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(libffi_COMPONENT_NAMES "")
if(DEFINED libffi_FIND_DEPENDENCY_NAMES)
  list(APPEND libffi_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES libffi_FIND_DEPENDENCY_NAMES)
else()
  set(libffi_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(libffi_PACKAGE_FOLDER_RELEASE "/home/bastian/.conan2/p/b/libff17aaffe888831/p")
set(libffi_BUILD_MODULES_PATHS_RELEASE )


set(libffi_INCLUDE_DIRS_RELEASE )
set(libffi_RES_DIRS_RELEASE )
set(libffi_DEFINITIONS_RELEASE "-DFFI_STATIC_BUILD")
set(libffi_SHARED_LINK_FLAGS_RELEASE )
set(libffi_EXE_LINK_FLAGS_RELEASE )
set(libffi_OBJECTS_RELEASE )
set(libffi_COMPILE_DEFINITIONS_RELEASE "FFI_STATIC_BUILD")
set(libffi_COMPILE_OPTIONS_C_RELEASE )
set(libffi_COMPILE_OPTIONS_CXX_RELEASE )
set(libffi_LIB_DIRS_RELEASE "${libffi_PACKAGE_FOLDER_RELEASE}/lib")
set(libffi_BIN_DIRS_RELEASE )
set(libffi_LIBRARY_TYPE_RELEASE STATIC)
set(libffi_IS_HOST_WINDOWS_RELEASE 0)
set(libffi_LIBS_RELEASE ffi)
set(libffi_SYSTEM_LIBS_RELEASE )
set(libffi_FRAMEWORK_DIRS_RELEASE )
set(libffi_FRAMEWORKS_RELEASE )
set(libffi_BUILD_DIRS_RELEASE )
set(libffi_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(libffi_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libffi_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libffi_COMPILE_OPTIONS_C_RELEASE}>")
set(libffi_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libffi_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libffi_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libffi_EXE_LINK_FLAGS_RELEASE}>")


set(libffi_COMPONENTS_RELEASE )