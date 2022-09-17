cmake_minimum_required(VERSION 3.8)

project(BmNodeEditor CXX)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)
set(OpenGL_GL_PREFERENCE LEGACY)

option(BUILD_SHARED_LIBS "Build as shared library" ON)
option(BUILD_DEBUG_POSTFIX_D "Append d suffix to debug libraries" OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

if(BUILD_DEBUG_POSTFIX_D)
    set(CMAKE_DEBUG_POSTFIX d)
endif()

find_package(Qt5 QUIET
    COMPONENTS
    Core
    Widgets
    Gui
    OpenGL
)

if (NOT Qt5_FOUND)
    message(FATAL_ERROR "Qt libraries were not found.")
endif()

# Unfortunately, as we have a split include/src, AUTOMOC doesn't work.
# We'll have to manually specify some files
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE CPP_HEADER_FILES
    src/nodes/internal/*.hpp
    src/models/image/*.hpp)

set(CPP_SOURCE_FILES
    main.cpp
    src/connection.cpp
    src/connectionblureffect.cpp
    src/connectiongeometry.cpp
    src/connectiongraphicsobject.cpp
    src/connectionpainter.cpp
    src/connectionstate.cpp
    src/connectionstyle.cpp
    src/datamodelregistry.cpp
    src/flowscene.cpp
    src/flowview.cpp
    src/flowviewstyle.cpp
    src/node.cpp
    src/nodeconnectioninteraction.cpp
    src/nodedatamodel.cpp
    src/nodegeometry.cpp
    src/nodegraphicsobject.cpp
    src/nodepainter.cpp
    src/nodestate.cpp
    src/nodestyle.cpp
    src/properties.cpp
    src/stylecollection.cpp

    src/models/image/imageloadermodel.cpp
    src/models/image/imageshowmodel.cpp
)

add_executable(${PROJECT_NAME}
    main.cpp
    ${CPP_HEADER_FILES}
    ${CPP_SOURCE_FILES}
    ./resources/resources.qrc
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/nodes/internal>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/models/image>
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::OpenGL
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
    NODE_EDITOR_SHARED
    PRIVATE
    NODE_EDITOR_EXPORTS
    #        NODE_DEBUG_DRAWING
)
