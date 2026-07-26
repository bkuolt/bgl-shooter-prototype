########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND libglvnd_COMPONENT_NAMES libglvnd::gldispatch libglvnd::opengl libglvnd::egl libglvnd::glx libglvnd::gles1 libglvnd::gles2 libglvnd::gl)
list(REMOVE_DUPLICATES libglvnd_COMPONENT_NAMES)
if(DEFINED libglvnd_FIND_DEPENDENCY_NAMES)
  list(APPEND libglvnd_FIND_DEPENDENCY_NAMES xorg xorg-proto)
  list(REMOVE_DUPLICATES libglvnd_FIND_DEPENDENCY_NAMES)
else()
  set(libglvnd_FIND_DEPENDENCY_NAMES xorg xorg-proto)
endif()
set(xorg_FIND_MODE "NO_MODULE")
set(xorg-proto_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(libglvnd_PACKAGE_FOLDER_RELEASE "/home/bastian/.conan2/p/b/libgl9b569f45967fa/p")
set(libglvnd_BUILD_MODULES_PATHS_RELEASE )


set(libglvnd_INCLUDE_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/include")
set(libglvnd_RES_DIRS_RELEASE )
set(libglvnd_DEFINITIONS_RELEASE )
set(libglvnd_SHARED_LINK_FLAGS_RELEASE )
set(libglvnd_EXE_LINK_FLAGS_RELEASE )
set(libglvnd_OBJECTS_RELEASE )
set(libglvnd_COMPILE_DEFINITIONS_RELEASE )
set(libglvnd_COMPILE_OPTIONS_C_RELEASE )
set(libglvnd_COMPILE_OPTIONS_CXX_RELEASE )
set(libglvnd_LIB_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/lib")
set(libglvnd_BIN_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/bin")
set(libglvnd_LIBRARY_TYPE_RELEASE SHARED)
set(libglvnd_IS_HOST_WINDOWS_RELEASE 0)
set(libglvnd_LIBS_RELEASE GL GLESv2 GLESv1_CM GLX EGL OpenGL GLdispatch)
set(libglvnd_SYSTEM_LIBS_RELEASE dl pthread m)
set(libglvnd_FRAMEWORK_DIRS_RELEASE )
set(libglvnd_FRAMEWORKS_RELEASE )
set(libglvnd_BUILD_DIRS_RELEASE )
set(libglvnd_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(libglvnd_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libglvnd_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libglvnd_COMPILE_OPTIONS_C_RELEASE}>")
set(libglvnd_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libglvnd_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libglvnd_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libglvnd_EXE_LINK_FLAGS_RELEASE}>")


set(libglvnd_COMPONENTS_RELEASE libglvnd::gldispatch libglvnd::opengl libglvnd::egl libglvnd::glx libglvnd::gles1 libglvnd::gles2 libglvnd::gl)
########### COMPONENT libglvnd::gl VARIABLES ############################################

set(libglvnd_libglvnd_gl_INCLUDE_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/include")
set(libglvnd_libglvnd_gl_LIB_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/lib")
set(libglvnd_libglvnd_gl_BIN_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/bin")
set(libglvnd_libglvnd_gl_LIBRARY_TYPE_RELEASE SHARED)
set(libglvnd_libglvnd_gl_IS_HOST_WINDOWS_RELEASE 0)
set(libglvnd_libglvnd_gl_RES_DIRS_RELEASE )
set(libglvnd_libglvnd_gl_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_gl_OBJECTS_RELEASE )
set(libglvnd_libglvnd_gl_COMPILE_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_gl_COMPILE_OPTIONS_C_RELEASE "")
set(libglvnd_libglvnd_gl_COMPILE_OPTIONS_CXX_RELEASE "")
set(libglvnd_libglvnd_gl_LIBS_RELEASE GL)
set(libglvnd_libglvnd_gl_SYSTEM_LIBS_RELEASE dl)
set(libglvnd_libglvnd_gl_FRAMEWORK_DIRS_RELEASE )
set(libglvnd_libglvnd_gl_FRAMEWORKS_RELEASE )
set(libglvnd_libglvnd_gl_DEPENDENCIES_RELEASE xorg::x11 libglvnd::glx libglvnd::gldispatch)
set(libglvnd_libglvnd_gl_SHARED_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_gl_EXE_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_gl_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(libglvnd_libglvnd_gl_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libglvnd_libglvnd_gl_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libglvnd_libglvnd_gl_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libglvnd_libglvnd_gl_EXE_LINK_FLAGS_RELEASE}>
)
set(libglvnd_libglvnd_gl_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libglvnd_libglvnd_gl_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libglvnd_libglvnd_gl_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT libglvnd::gles2 VARIABLES ############################################

set(libglvnd_libglvnd_gles2_INCLUDE_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/include")
set(libglvnd_libglvnd_gles2_LIB_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/lib")
set(libglvnd_libglvnd_gles2_BIN_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/bin")
set(libglvnd_libglvnd_gles2_LIBRARY_TYPE_RELEASE SHARED)
set(libglvnd_libglvnd_gles2_IS_HOST_WINDOWS_RELEASE 0)
set(libglvnd_libglvnd_gles2_RES_DIRS_RELEASE )
set(libglvnd_libglvnd_gles2_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_gles2_OBJECTS_RELEASE )
set(libglvnd_libglvnd_gles2_COMPILE_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_gles2_COMPILE_OPTIONS_C_RELEASE "")
set(libglvnd_libglvnd_gles2_COMPILE_OPTIONS_CXX_RELEASE "")
set(libglvnd_libglvnd_gles2_LIBS_RELEASE GLESv2)
set(libglvnd_libglvnd_gles2_SYSTEM_LIBS_RELEASE )
set(libglvnd_libglvnd_gles2_FRAMEWORK_DIRS_RELEASE )
set(libglvnd_libglvnd_gles2_FRAMEWORKS_RELEASE )
set(libglvnd_libglvnd_gles2_DEPENDENCIES_RELEASE libglvnd::gldispatch)
set(libglvnd_libglvnd_gles2_SHARED_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_gles2_EXE_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_gles2_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(libglvnd_libglvnd_gles2_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libglvnd_libglvnd_gles2_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libglvnd_libglvnd_gles2_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libglvnd_libglvnd_gles2_EXE_LINK_FLAGS_RELEASE}>
)
set(libglvnd_libglvnd_gles2_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libglvnd_libglvnd_gles2_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libglvnd_libglvnd_gles2_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT libglvnd::gles1 VARIABLES ############################################

set(libglvnd_libglvnd_gles1_INCLUDE_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/include")
set(libglvnd_libglvnd_gles1_LIB_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/lib")
set(libglvnd_libglvnd_gles1_BIN_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/bin")
set(libglvnd_libglvnd_gles1_LIBRARY_TYPE_RELEASE SHARED)
set(libglvnd_libglvnd_gles1_IS_HOST_WINDOWS_RELEASE 0)
set(libglvnd_libglvnd_gles1_RES_DIRS_RELEASE )
set(libglvnd_libglvnd_gles1_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_gles1_OBJECTS_RELEASE )
set(libglvnd_libglvnd_gles1_COMPILE_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_gles1_COMPILE_OPTIONS_C_RELEASE "")
set(libglvnd_libglvnd_gles1_COMPILE_OPTIONS_CXX_RELEASE "")
set(libglvnd_libglvnd_gles1_LIBS_RELEASE GLESv1_CM)
set(libglvnd_libglvnd_gles1_SYSTEM_LIBS_RELEASE )
set(libglvnd_libglvnd_gles1_FRAMEWORK_DIRS_RELEASE )
set(libglvnd_libglvnd_gles1_FRAMEWORKS_RELEASE )
set(libglvnd_libglvnd_gles1_DEPENDENCIES_RELEASE libglvnd::gldispatch)
set(libglvnd_libglvnd_gles1_SHARED_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_gles1_EXE_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_gles1_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(libglvnd_libglvnd_gles1_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libglvnd_libglvnd_gles1_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libglvnd_libglvnd_gles1_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libglvnd_libglvnd_gles1_EXE_LINK_FLAGS_RELEASE}>
)
set(libglvnd_libglvnd_gles1_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libglvnd_libglvnd_gles1_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libglvnd_libglvnd_gles1_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT libglvnd::glx VARIABLES ############################################

set(libglvnd_libglvnd_glx_INCLUDE_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/include")
set(libglvnd_libglvnd_glx_LIB_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/lib")
set(libglvnd_libglvnd_glx_BIN_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/bin")
set(libglvnd_libglvnd_glx_LIBRARY_TYPE_RELEASE SHARED)
set(libglvnd_libglvnd_glx_IS_HOST_WINDOWS_RELEASE 0)
set(libglvnd_libglvnd_glx_RES_DIRS_RELEASE )
set(libglvnd_libglvnd_glx_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_glx_OBJECTS_RELEASE )
set(libglvnd_libglvnd_glx_COMPILE_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_glx_COMPILE_OPTIONS_C_RELEASE "")
set(libglvnd_libglvnd_glx_COMPILE_OPTIONS_CXX_RELEASE "")
set(libglvnd_libglvnd_glx_LIBS_RELEASE GLX)
set(libglvnd_libglvnd_glx_SYSTEM_LIBS_RELEASE dl)
set(libglvnd_libglvnd_glx_FRAMEWORK_DIRS_RELEASE )
set(libglvnd_libglvnd_glx_FRAMEWORKS_RELEASE )
set(libglvnd_libglvnd_glx_DEPENDENCIES_RELEASE xorg::x11 xorg-proto::glproto libglvnd::gldispatch)
set(libglvnd_libglvnd_glx_SHARED_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_glx_EXE_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_glx_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(libglvnd_libglvnd_glx_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libglvnd_libglvnd_glx_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libglvnd_libglvnd_glx_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libglvnd_libglvnd_glx_EXE_LINK_FLAGS_RELEASE}>
)
set(libglvnd_libglvnd_glx_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libglvnd_libglvnd_glx_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libglvnd_libglvnd_glx_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT libglvnd::egl VARIABLES ############################################

set(libglvnd_libglvnd_egl_INCLUDE_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/include")
set(libglvnd_libglvnd_egl_LIB_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/lib")
set(libglvnd_libglvnd_egl_BIN_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/bin")
set(libglvnd_libglvnd_egl_LIBRARY_TYPE_RELEASE SHARED)
set(libglvnd_libglvnd_egl_IS_HOST_WINDOWS_RELEASE 0)
set(libglvnd_libglvnd_egl_RES_DIRS_RELEASE )
set(libglvnd_libglvnd_egl_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_egl_OBJECTS_RELEASE )
set(libglvnd_libglvnd_egl_COMPILE_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_egl_COMPILE_OPTIONS_C_RELEASE "")
set(libglvnd_libglvnd_egl_COMPILE_OPTIONS_CXX_RELEASE "")
set(libglvnd_libglvnd_egl_LIBS_RELEASE EGL)
set(libglvnd_libglvnd_egl_SYSTEM_LIBS_RELEASE pthread dl m)
set(libglvnd_libglvnd_egl_FRAMEWORK_DIRS_RELEASE )
set(libglvnd_libglvnd_egl_FRAMEWORKS_RELEASE )
set(libglvnd_libglvnd_egl_DEPENDENCIES_RELEASE libglvnd::gldispatch xorg::x11)
set(libglvnd_libglvnd_egl_SHARED_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_egl_EXE_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_egl_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(libglvnd_libglvnd_egl_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libglvnd_libglvnd_egl_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libglvnd_libglvnd_egl_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libglvnd_libglvnd_egl_EXE_LINK_FLAGS_RELEASE}>
)
set(libglvnd_libglvnd_egl_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libglvnd_libglvnd_egl_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libglvnd_libglvnd_egl_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT libglvnd::opengl VARIABLES ############################################

set(libglvnd_libglvnd_opengl_INCLUDE_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/include")
set(libglvnd_libglvnd_opengl_LIB_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/lib")
set(libglvnd_libglvnd_opengl_BIN_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/bin")
set(libglvnd_libglvnd_opengl_LIBRARY_TYPE_RELEASE SHARED)
set(libglvnd_libglvnd_opengl_IS_HOST_WINDOWS_RELEASE 0)
set(libglvnd_libglvnd_opengl_RES_DIRS_RELEASE )
set(libglvnd_libglvnd_opengl_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_opengl_OBJECTS_RELEASE )
set(libglvnd_libglvnd_opengl_COMPILE_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_opengl_COMPILE_OPTIONS_C_RELEASE "")
set(libglvnd_libglvnd_opengl_COMPILE_OPTIONS_CXX_RELEASE "")
set(libglvnd_libglvnd_opengl_LIBS_RELEASE OpenGL)
set(libglvnd_libglvnd_opengl_SYSTEM_LIBS_RELEASE )
set(libglvnd_libglvnd_opengl_FRAMEWORK_DIRS_RELEASE )
set(libglvnd_libglvnd_opengl_FRAMEWORKS_RELEASE )
set(libglvnd_libglvnd_opengl_DEPENDENCIES_RELEASE libglvnd::gldispatch)
set(libglvnd_libglvnd_opengl_SHARED_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_opengl_EXE_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_opengl_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(libglvnd_libglvnd_opengl_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libglvnd_libglvnd_opengl_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libglvnd_libglvnd_opengl_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libglvnd_libglvnd_opengl_EXE_LINK_FLAGS_RELEASE}>
)
set(libglvnd_libglvnd_opengl_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libglvnd_libglvnd_opengl_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libglvnd_libglvnd_opengl_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT libglvnd::gldispatch VARIABLES ############################################

set(libglvnd_libglvnd_gldispatch_INCLUDE_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/include")
set(libglvnd_libglvnd_gldispatch_LIB_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/lib")
set(libglvnd_libglvnd_gldispatch_BIN_DIRS_RELEASE "${libglvnd_PACKAGE_FOLDER_RELEASE}/bin")
set(libglvnd_libglvnd_gldispatch_LIBRARY_TYPE_RELEASE SHARED)
set(libglvnd_libglvnd_gldispatch_IS_HOST_WINDOWS_RELEASE 0)
set(libglvnd_libglvnd_gldispatch_RES_DIRS_RELEASE )
set(libglvnd_libglvnd_gldispatch_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_gldispatch_OBJECTS_RELEASE )
set(libglvnd_libglvnd_gldispatch_COMPILE_DEFINITIONS_RELEASE )
set(libglvnd_libglvnd_gldispatch_COMPILE_OPTIONS_C_RELEASE "")
set(libglvnd_libglvnd_gldispatch_COMPILE_OPTIONS_CXX_RELEASE "")
set(libglvnd_libglvnd_gldispatch_LIBS_RELEASE GLdispatch)
set(libglvnd_libglvnd_gldispatch_SYSTEM_LIBS_RELEASE pthread dl)
set(libglvnd_libglvnd_gldispatch_FRAMEWORK_DIRS_RELEASE )
set(libglvnd_libglvnd_gldispatch_FRAMEWORKS_RELEASE )
set(libglvnd_libglvnd_gldispatch_DEPENDENCIES_RELEASE )
set(libglvnd_libglvnd_gldispatch_SHARED_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_gldispatch_EXE_LINK_FLAGS_RELEASE )
set(libglvnd_libglvnd_gldispatch_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(libglvnd_libglvnd_gldispatch_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${libglvnd_libglvnd_gldispatch_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${libglvnd_libglvnd_gldispatch_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${libglvnd_libglvnd_gldispatch_EXE_LINK_FLAGS_RELEASE}>
)
set(libglvnd_libglvnd_gldispatch_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${libglvnd_libglvnd_gldispatch_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${libglvnd_libglvnd_gldispatch_COMPILE_OPTIONS_C_RELEASE}>")