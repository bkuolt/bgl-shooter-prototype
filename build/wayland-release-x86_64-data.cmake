########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND wayland_COMPONENT_NAMES wayland::wayland-scanner wayland::wayland-server wayland::wayland-client wayland::wayland-egl-backend wayland::wayland-cursor wayland::wayland-egl)
list(REMOVE_DUPLICATES wayland_COMPONENT_NAMES)
if(DEFINED wayland_FIND_DEPENDENCY_NAMES)
  list(APPEND wayland_FIND_DEPENDENCY_NAMES libffi libxml2 expat)
  list(REMOVE_DUPLICATES wayland_FIND_DEPENDENCY_NAMES)
else()
  set(wayland_FIND_DEPENDENCY_NAMES libffi libxml2 expat)
endif()
set(libffi_FIND_MODE "NO_MODULE")
set(libxml2_FIND_MODE "NO_MODULE")
set(expat_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(wayland_PACKAGE_FOLDER_RELEASE "/home/bastian/.conan2/p/b/wayla392bebab4b8c8/p")
set(wayland_BUILD_MODULES_PATHS_RELEASE )


set(wayland_INCLUDE_DIRS_RELEASE )
set(wayland_RES_DIRS_RELEASE "${wayland_PACKAGE_FOLDER_RELEASE}/res")
set(wayland_DEFINITIONS_RELEASE )
set(wayland_SHARED_LINK_FLAGS_RELEASE )
set(wayland_EXE_LINK_FLAGS_RELEASE )
set(wayland_OBJECTS_RELEASE )
set(wayland_COMPILE_DEFINITIONS_RELEASE )
set(wayland_COMPILE_OPTIONS_C_RELEASE )
set(wayland_COMPILE_OPTIONS_CXX_RELEASE )
set(wayland_LIB_DIRS_RELEASE "${wayland_PACKAGE_FOLDER_RELEASE}/lib")
set(wayland_BIN_DIRS_RELEASE )
set(wayland_LIBRARY_TYPE_RELEASE STATIC)
set(wayland_IS_HOST_WINDOWS_RELEASE 0)
set(wayland_LIBS_RELEASE wayland-egl wayland-cursor wayland-client wayland-server)
set(wayland_SYSTEM_LIBS_RELEASE pthread m rt)
set(wayland_FRAMEWORK_DIRS_RELEASE )
set(wayland_FRAMEWORKS_RELEASE )
set(wayland_BUILD_DIRS_RELEASE )
set(wayland_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(wayland_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${wayland_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${wayland_COMPILE_OPTIONS_C_RELEASE}>")
set(wayland_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${wayland_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${wayland_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${wayland_EXE_LINK_FLAGS_RELEASE}>")


set(wayland_COMPONENTS_RELEASE wayland::wayland-scanner wayland::wayland-server wayland::wayland-client wayland::wayland-egl-backend wayland::wayland-cursor wayland::wayland-egl)
########### COMPONENT wayland::wayland-egl VARIABLES ############################################

set(wayland_wayland_wayland-egl_INCLUDE_DIRS_RELEASE )
set(wayland_wayland_wayland-egl_LIB_DIRS_RELEASE "${wayland_PACKAGE_FOLDER_RELEASE}/lib")
set(wayland_wayland_wayland-egl_BIN_DIRS_RELEASE )
set(wayland_wayland_wayland-egl_LIBRARY_TYPE_RELEASE STATIC)
set(wayland_wayland_wayland-egl_IS_HOST_WINDOWS_RELEASE 0)
set(wayland_wayland_wayland-egl_RES_DIRS_RELEASE )
set(wayland_wayland_wayland-egl_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-egl_OBJECTS_RELEASE )
set(wayland_wayland_wayland-egl_COMPILE_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-egl_COMPILE_OPTIONS_C_RELEASE "")
set(wayland_wayland_wayland-egl_COMPILE_OPTIONS_CXX_RELEASE "")
set(wayland_wayland_wayland-egl_LIBS_RELEASE wayland-egl)
set(wayland_wayland_wayland-egl_SYSTEM_LIBS_RELEASE )
set(wayland_wayland_wayland-egl_FRAMEWORK_DIRS_RELEASE )
set(wayland_wayland_wayland-egl_FRAMEWORKS_RELEASE )
set(wayland_wayland_wayland-egl_DEPENDENCIES_RELEASE wayland::wayland-client)
set(wayland_wayland_wayland-egl_SHARED_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-egl_EXE_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-egl_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(wayland_wayland_wayland-egl_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${wayland_wayland_wayland-egl_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${wayland_wayland_wayland-egl_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${wayland_wayland_wayland-egl_EXE_LINK_FLAGS_RELEASE}>
)
set(wayland_wayland_wayland-egl_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${wayland_wayland_wayland-egl_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${wayland_wayland_wayland-egl_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT wayland::wayland-cursor VARIABLES ############################################

set(wayland_wayland_wayland-cursor_INCLUDE_DIRS_RELEASE )
set(wayland_wayland_wayland-cursor_LIB_DIRS_RELEASE "${wayland_PACKAGE_FOLDER_RELEASE}/lib")
set(wayland_wayland_wayland-cursor_BIN_DIRS_RELEASE )
set(wayland_wayland_wayland-cursor_LIBRARY_TYPE_RELEASE STATIC)
set(wayland_wayland_wayland-cursor_IS_HOST_WINDOWS_RELEASE 0)
set(wayland_wayland_wayland-cursor_RES_DIRS_RELEASE )
set(wayland_wayland_wayland-cursor_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-cursor_OBJECTS_RELEASE )
set(wayland_wayland_wayland-cursor_COMPILE_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-cursor_COMPILE_OPTIONS_C_RELEASE "")
set(wayland_wayland_wayland-cursor_COMPILE_OPTIONS_CXX_RELEASE "")
set(wayland_wayland_wayland-cursor_LIBS_RELEASE wayland-cursor)
set(wayland_wayland_wayland-cursor_SYSTEM_LIBS_RELEASE )
set(wayland_wayland_wayland-cursor_FRAMEWORK_DIRS_RELEASE )
set(wayland_wayland_wayland-cursor_FRAMEWORKS_RELEASE )
set(wayland_wayland_wayland-cursor_DEPENDENCIES_RELEASE wayland::wayland-client)
set(wayland_wayland_wayland-cursor_SHARED_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-cursor_EXE_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-cursor_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(wayland_wayland_wayland-cursor_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${wayland_wayland_wayland-cursor_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${wayland_wayland_wayland-cursor_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${wayland_wayland_wayland-cursor_EXE_LINK_FLAGS_RELEASE}>
)
set(wayland_wayland_wayland-cursor_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${wayland_wayland_wayland-cursor_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${wayland_wayland_wayland-cursor_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT wayland::wayland-egl-backend VARIABLES ############################################

set(wayland_wayland_wayland-egl-backend_INCLUDE_DIRS_RELEASE )
set(wayland_wayland_wayland-egl-backend_LIB_DIRS_RELEASE "${wayland_PACKAGE_FOLDER_RELEASE}/lib")
set(wayland_wayland_wayland-egl-backend_BIN_DIRS_RELEASE )
set(wayland_wayland_wayland-egl-backend_LIBRARY_TYPE_RELEASE STATIC)
set(wayland_wayland_wayland-egl-backend_IS_HOST_WINDOWS_RELEASE 0)
set(wayland_wayland_wayland-egl-backend_RES_DIRS_RELEASE )
set(wayland_wayland_wayland-egl-backend_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-egl-backend_OBJECTS_RELEASE )
set(wayland_wayland_wayland-egl-backend_COMPILE_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-egl-backend_COMPILE_OPTIONS_C_RELEASE "")
set(wayland_wayland_wayland-egl-backend_COMPILE_OPTIONS_CXX_RELEASE "")
set(wayland_wayland_wayland-egl-backend_LIBS_RELEASE )
set(wayland_wayland_wayland-egl-backend_SYSTEM_LIBS_RELEASE )
set(wayland_wayland_wayland-egl-backend_FRAMEWORK_DIRS_RELEASE )
set(wayland_wayland_wayland-egl-backend_FRAMEWORKS_RELEASE )
set(wayland_wayland_wayland-egl-backend_DEPENDENCIES_RELEASE )
set(wayland_wayland_wayland-egl-backend_SHARED_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-egl-backend_EXE_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-egl-backend_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(wayland_wayland_wayland-egl-backend_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${wayland_wayland_wayland-egl-backend_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${wayland_wayland_wayland-egl-backend_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${wayland_wayland_wayland-egl-backend_EXE_LINK_FLAGS_RELEASE}>
)
set(wayland_wayland_wayland-egl-backend_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${wayland_wayland_wayland-egl-backend_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${wayland_wayland_wayland-egl-backend_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT wayland::wayland-client VARIABLES ############################################

set(wayland_wayland_wayland-client_INCLUDE_DIRS_RELEASE )
set(wayland_wayland_wayland-client_LIB_DIRS_RELEASE "${wayland_PACKAGE_FOLDER_RELEASE}/lib")
set(wayland_wayland_wayland-client_BIN_DIRS_RELEASE )
set(wayland_wayland_wayland-client_LIBRARY_TYPE_RELEASE STATIC)
set(wayland_wayland_wayland-client_IS_HOST_WINDOWS_RELEASE 0)
set(wayland_wayland_wayland-client_RES_DIRS_RELEASE "${wayland_PACKAGE_FOLDER_RELEASE}/res")
set(wayland_wayland_wayland-client_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-client_OBJECTS_RELEASE )
set(wayland_wayland_wayland-client_COMPILE_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-client_COMPILE_OPTIONS_C_RELEASE "")
set(wayland_wayland_wayland-client_COMPILE_OPTIONS_CXX_RELEASE "")
set(wayland_wayland_wayland-client_LIBS_RELEASE wayland-client)
set(wayland_wayland_wayland-client_SYSTEM_LIBS_RELEASE pthread m rt)
set(wayland_wayland_wayland-client_FRAMEWORK_DIRS_RELEASE )
set(wayland_wayland_wayland-client_FRAMEWORKS_RELEASE )
set(wayland_wayland_wayland-client_DEPENDENCIES_RELEASE libffi::libffi)
set(wayland_wayland_wayland-client_SHARED_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-client_EXE_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-client_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(wayland_wayland_wayland-client_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${wayland_wayland_wayland-client_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${wayland_wayland_wayland-client_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${wayland_wayland_wayland-client_EXE_LINK_FLAGS_RELEASE}>
)
set(wayland_wayland_wayland-client_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${wayland_wayland_wayland-client_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${wayland_wayland_wayland-client_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT wayland::wayland-server VARIABLES ############################################

set(wayland_wayland_wayland-server_INCLUDE_DIRS_RELEASE )
set(wayland_wayland_wayland-server_LIB_DIRS_RELEASE "${wayland_PACKAGE_FOLDER_RELEASE}/lib")
set(wayland_wayland_wayland-server_BIN_DIRS_RELEASE )
set(wayland_wayland_wayland-server_LIBRARY_TYPE_RELEASE STATIC)
set(wayland_wayland_wayland-server_IS_HOST_WINDOWS_RELEASE 0)
set(wayland_wayland_wayland-server_RES_DIRS_RELEASE "${wayland_PACKAGE_FOLDER_RELEASE}/res")
set(wayland_wayland_wayland-server_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-server_OBJECTS_RELEASE )
set(wayland_wayland_wayland-server_COMPILE_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-server_COMPILE_OPTIONS_C_RELEASE "")
set(wayland_wayland_wayland-server_COMPILE_OPTIONS_CXX_RELEASE "")
set(wayland_wayland_wayland-server_LIBS_RELEASE wayland-server)
set(wayland_wayland_wayland-server_SYSTEM_LIBS_RELEASE pthread m rt)
set(wayland_wayland_wayland-server_FRAMEWORK_DIRS_RELEASE )
set(wayland_wayland_wayland-server_FRAMEWORKS_RELEASE )
set(wayland_wayland_wayland-server_DEPENDENCIES_RELEASE libffi::libffi)
set(wayland_wayland_wayland-server_SHARED_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-server_EXE_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-server_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(wayland_wayland_wayland-server_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${wayland_wayland_wayland-server_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${wayland_wayland_wayland-server_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${wayland_wayland_wayland-server_EXE_LINK_FLAGS_RELEASE}>
)
set(wayland_wayland_wayland-server_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${wayland_wayland_wayland-server_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${wayland_wayland_wayland-server_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT wayland::wayland-scanner VARIABLES ############################################

set(wayland_wayland_wayland-scanner_INCLUDE_DIRS_RELEASE )
set(wayland_wayland_wayland-scanner_LIB_DIRS_RELEASE )
set(wayland_wayland_wayland-scanner_BIN_DIRS_RELEASE )
set(wayland_wayland_wayland-scanner_LIBRARY_TYPE_RELEASE STATIC)
set(wayland_wayland_wayland-scanner_IS_HOST_WINDOWS_RELEASE 0)
set(wayland_wayland_wayland-scanner_RES_DIRS_RELEASE "${wayland_PACKAGE_FOLDER_RELEASE}/res")
set(wayland_wayland_wayland-scanner_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-scanner_OBJECTS_RELEASE )
set(wayland_wayland_wayland-scanner_COMPILE_DEFINITIONS_RELEASE )
set(wayland_wayland_wayland-scanner_COMPILE_OPTIONS_C_RELEASE "")
set(wayland_wayland_wayland-scanner_COMPILE_OPTIONS_CXX_RELEASE "")
set(wayland_wayland_wayland-scanner_LIBS_RELEASE )
set(wayland_wayland_wayland-scanner_SYSTEM_LIBS_RELEASE )
set(wayland_wayland_wayland-scanner_FRAMEWORK_DIRS_RELEASE )
set(wayland_wayland_wayland-scanner_FRAMEWORKS_RELEASE )
set(wayland_wayland_wayland-scanner_DEPENDENCIES_RELEASE expat::expat LibXml2::LibXml2)
set(wayland_wayland_wayland-scanner_SHARED_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-scanner_EXE_LINK_FLAGS_RELEASE )
set(wayland_wayland_wayland-scanner_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(wayland_wayland_wayland-scanner_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${wayland_wayland_wayland-scanner_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${wayland_wayland_wayland-scanner_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${wayland_wayland_wayland-scanner_EXE_LINK_FLAGS_RELEASE}>
)
set(wayland_wayland_wayland-scanner_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${wayland_wayland_wayland-scanner_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${wayland_wayland_wayland-scanner_COMPILE_OPTIONS_C_RELEASE}>")