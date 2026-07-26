# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/libxml2-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${libxml2_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${libxml2_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET LibXml2::LibXml2)
    add_library(LibXml2::LibXml2 INTERFACE IMPORTED)
    message(${libxml2_MESSAGE_MODE} "Conan: Target declared 'LibXml2::LibXml2'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/libxml2-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()