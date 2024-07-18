cmake_minimum_required( VERSION 3.6 )
project( 01prims )

# 2.Configuration

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)


# 3. Boilerplate

set(USD_LIBRARY_DIRECTORY /usr/local/lib)
set(USD_INCLUDE_DIRECTORY /usr/local/include)
set(PYTHON_INCLUDE_PATH /usr/local/include/python3.11)
set(PXR_CONFIG_CMAKE "/usr/local/pxrConfig.cmake"
    CACHE
    STRING
    "Path to the pxrConfig.cmake file, located in the USD install folder by default."
)

find_library(PYTHON_LIBRARY NAMES python3.11 python3.10 python3 HINTS /usr/local/lib /usr/lib)
find_library(USD_BOOST_PYTHON boost_python311 HINTS ${USD_LIBRARY_DIRECTORY})


# find_library(USD_KIND usd_kind HINTS ${USD_LIBRARY_DIRECTORY})
# find_package(pxr REQUIRED)

include(${PXR_CONFIG_CMAKE})

add_executable(Prims01 Prims01.cpp)

target_include_directories(Prims01
	PUBLIC
		${PYTHON_INCLUDE_PATH}
		${USD_INCLUDE_DIRECTORY}
		${PXR_INCLUDE_DIRS}
	)


#
target_link_libraries(
Prims01
	${PYTHON_LIBRARY}
    ${USD_BOOST_PYTHON}
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
)
