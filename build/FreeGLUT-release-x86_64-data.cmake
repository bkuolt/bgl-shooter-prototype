########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND freeglut_COMPONENT_NAMES FreeGLUT::freeglut_static)
list(REMOVE_DUPLICATES freeglut_COMPONENT_NAMES)
if(DEFINED freeglut_FIND_DEPENDENCY_NAMES)
  list(APPEND freeglut_FIND_DEPENDENCY_NAMES mesa-glu libglvnd xorg)
  list(REMOVE_DUPLICATES freeglut_FIND_DEPENDENCY_NAMES)
else()
  set(freeglut_FIND_DEPENDENCY_NAMES mesa-glu libglvnd xorg)
endif()
set(mesa-glu_FIND_MODE "NO_MODULE")
set(libglvnd_FIND_MODE "NO_MODULE")
set(xorg_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(freeglut_PACKAGE_FOLDER_RELEASE "/home/bastian/.conan2/p/b/freeg36ee898bc1ea9/p")
set(freeglut_BUILD_MODULES_PATHS_RELEASE )


set(freeglut_INCLUDE_DIRS_RELEASE "${freeglut_PACKAGE_FOLDER_RELEASE}/include")
set(freeglut_RES_DIRS_RELEASE )
set(freeglut_DEFINITIONS_RELEASE )
set(freeglut_SHARED_LINK_FLAGS_RELEASE )
set(freeglut_EXE_LINK_FLAGS_RELEASE )
set(freeglut_OBJECTS_RELEASE )
set(freeglut_COMPILE_DEFINITIONS_RELEASE )
set(freeglut_COMPILE_OPTIONS_C_RELEASE )
set(freeglut_COMPILE_OPTIONS_CXX_RELEASE )
set(freeglut_LIB_DIRS_RELEASE "${freeglut_PACKAGE_FOLDER_RELEASE}/lib")
set(freeglut_BIN_DIRS_RELEASE )
set(freeglut_LIBRARY_TYPE_RELEASE STATIC)
set(freeglut_IS_HOST_WINDOWS_RELEASE 0)
set(freeglut_LIBS_RELEASE glut)
set(freeglut_SYSTEM_LIBS_RELEASE pthread m dl rt)
set(freeglut_FRAMEWORK_DIRS_RELEASE )
set(freeglut_FRAMEWORKS_RELEASE )
set(freeglut_BUILD_DIRS_RELEASE )
set(freeglut_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(freeglut_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${freeglut_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${freeglut_COMPILE_OPTIONS_C_RELEASE}>")
set(freeglut_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${freeglut_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${freeglut_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${freeglut_EXE_LINK_FLAGS_RELEASE}>")


set(freeglut_COMPONENTS_RELEASE FreeGLUT::freeglut_static)
########### COMPONENT FreeGLUT::freeglut_static VARIABLES ############################################

set(freeglut_FreeGLUT_freeglut_static_INCLUDE_DIRS_RELEASE "${freeglut_PACKAGE_FOLDER_RELEASE}/include")
set(freeglut_FreeGLUT_freeglut_static_LIB_DIRS_RELEASE "${freeglut_PACKAGE_FOLDER_RELEASE}/lib")
set(freeglut_FreeGLUT_freeglut_static_BIN_DIRS_RELEASE )
set(freeglut_FreeGLUT_freeglut_static_LIBRARY_TYPE_RELEASE STATIC)
set(freeglut_FreeGLUT_freeglut_static_IS_HOST_WINDOWS_RELEASE 0)
set(freeglut_FreeGLUT_freeglut_static_RES_DIRS_RELEASE )
set(freeglut_FreeGLUT_freeglut_static_DEFINITIONS_RELEASE )
set(freeglut_FreeGLUT_freeglut_static_OBJECTS_RELEASE )
set(freeglut_FreeGLUT_freeglut_static_COMPILE_DEFINITIONS_RELEASE )
set(freeglut_FreeGLUT_freeglut_static_COMPILE_OPTIONS_C_RELEASE "")
set(freeglut_FreeGLUT_freeglut_static_COMPILE_OPTIONS_CXX_RELEASE "")
set(freeglut_FreeGLUT_freeglut_static_LIBS_RELEASE glut)
set(freeglut_FreeGLUT_freeglut_static_SYSTEM_LIBS_RELEASE pthread m dl rt)
set(freeglut_FreeGLUT_freeglut_static_FRAMEWORK_DIRS_RELEASE )
set(freeglut_FreeGLUT_freeglut_static_FRAMEWORKS_RELEASE )
set(freeglut_FreeGLUT_freeglut_static_DEPENDENCIES_RELEASE libglvnd::gl libglvnd::opengl xorg::xorg mesa-glu::mesa-glu)
set(freeglut_FreeGLUT_freeglut_static_SHARED_LINK_FLAGS_RELEASE )
set(freeglut_FreeGLUT_freeglut_static_EXE_LINK_FLAGS_RELEASE )
set(freeglut_FreeGLUT_freeglut_static_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(freeglut_FreeGLUT_freeglut_static_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${freeglut_FreeGLUT_freeglut_static_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${freeglut_FreeGLUT_freeglut_static_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${freeglut_FreeGLUT_freeglut_static_EXE_LINK_FLAGS_RELEASE}>
)
set(freeglut_FreeGLUT_freeglut_static_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${freeglut_FreeGLUT_freeglut_static_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${freeglut_FreeGLUT_freeglut_static_COMPILE_OPTIONS_C_RELEASE}>")