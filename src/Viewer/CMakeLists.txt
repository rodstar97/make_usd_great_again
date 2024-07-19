
cmake_minimum_required(VERSION 3.27)
project(Viewer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_BUILD_TYPE=Debug)


set(LIBRARY_DIRECTORY /usr/local/lib)
set(INCLUDE_DIRECTORY /usr/local/include)
set(PYTHON_INCLUDE_PATH /usr/local/include/python3.11)
set(USD_LIBRARY_DIRECTORY /usr/local/lib)
set(USD_INCLUDE_DIRECTORY /usr/local/include)
set(PYTHON_INCLUDE_PATH /usr/local/include/python3.11)
set(PXR_CONFIG_CMAKE "/usr/local/pxrConfig.cmake"
    CACHE
    STRING
    "Path to the pxrConfig.cmake file, located in the USD install folder by default."
)


find_package(Qt6 COMPONENTS Widgets OpenGL OpenGLWidgets REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_library(PYTHON_LIBRARY NAMES python3.11 python3.10 python3 HINTS /usr/local/lib /usr/lib)
find_library(USD_BOOST_PYTHON boost_python311 HINTS ${USD_LIBRARY_DIRECTORY})



add_executable(viewer main.cpp viewer.cpp viewer.h scene.h scene.cpp)

include_directories(${Qt6Widgets_INCLUDE_DIRS} ${Qt6OpenGL_INCLUDE_DIRS} ${Qt6OpenGLWidgets_INCLUDE_DIRS})
include(${PXR_CONFIG_CMAKE})



target_include_directories(viewer
	PUBLIC
		${PYTHON_INCLUDE_PATH}
		${INCLUDE_DIRECTORY}
        ${USD_INCLUDE_DIRECTORY}
		${PXR_INCLUDE_DIRS}
	)

message(STATUS "Qt6Widgets_INCLUDE_DIRS: ${Qt6Widgets_INCLUDE_DIRS}")
message(STATUS "Qt6OpenGL_INCLUDE_DIRS: ${Qt6OpenGL_INCLUDE_DIRS}")
message(STATUS "Qt6OpenGLWidgets_INCLUDE_DIRS: ${Qt6OpenGLWidgets_INCLUDE_DIRS}")




target_link_libraries(viewer
    PUBLIC
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARY}
    ${PYTHON_LIBRARY}
    ${USD_BOOST_PYTHON}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    usd_kind
	usd_sdf
	usd_tf
	usd_usd
	usd_usdGeom
	usd_usdUtils
	usd_arch
	usd_vt
	usd_usdImagingGL
	usd_gf
    usd_glf
  
    
)
#install(TARGETS switch_demo_qt DESTINATION . ) 

#nstall(FILES  switch.usda switch.ma board.usda  DESTINATION . )

#WinDeployQt(TARGET switch_demo_qt QMLDIR ${CMAKE_CURRENT_SOURCE_DIR})
#install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../../windeployqt/ DESTINATION . )