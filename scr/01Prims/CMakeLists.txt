cmake_minimum_required( VERSION 3.6 )
project( 01prims )

# 2.Configuration

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)


# 3. Boilerplate

set(USD_LIBRARY_DIRECTORY /usr/local/lib)
set(USD_INCLUDE_DIRECTORY /usr/local/include)
set(PYTHON_INCLUDE_PATH /usr/local/include/python3.11)


find_library(PYTHON_LIBRARY NAMES python3.11 python3.10 python3 HINTS /usr/local/lib /usr/lib)
find_library(USD_BOOST_PYTHON boost_python311 HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_KIND usd_kind HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_SDF usd_sdf HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_TF usd_tf HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_USD usd_usd HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_USDGEOM usd_usdGeom HINTS ${USD_LIBRARY_DIRECTORY})
find_library(USD_USDUTILS usd_usdUtils HINTS ${USD_LIBRARY_DIRECTORY})





add_executable(Prims01 Prims01.cpp)

target_include_directories(Prims01
PUBLIC
	${PYTHON_INCLUDE_PATH}
	${USD_INCLUDE_DIRECTORY}
)


#
target_link_libraries(
Prims01
	${PYTHON_LIBRARY}
    ${USD_BOOST_PYTHON}
    ${USD_KIND}
	${USD_SDF}
	${USD_TF}
	${USD_USD}
	${USD_USDGEOM}
	${USD_USDUTILS}
)
