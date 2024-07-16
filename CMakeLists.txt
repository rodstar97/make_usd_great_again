cmake_minimum_required( VERSION 3.6 )
project( CPPUSD01 )

# 2.Configuration
#add_compile_options(-Wno-deprecated)  # This is just to avoid some spammy warnings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # This line is optional. It's just for certain IDEs to use
set(CMAKE_CXX_STANDARD 17)


# 3. Boilerplate
# set(USD_LIBRARY_DIRECTORY $ENV{USD_INSTALL_ROOT}/lib)
# set(USD_INCLUDE_DIRECTORY $ENV{USD_INSTALL_ROOT}/include)
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

#find_package(PythonLibs REQUIRED)



add_executable(test scr/main.cpp)

target_include_directories(test
PUBLIC
	${PYTHON_INCLUDE_PATH}
	${USD_INCLUDE_DIRECTORY}
)


#
target_link_libraries(
test
	${PYTHON_LIBRARY}
    ${USD_BOOST_PYTHON}
    ${USD_KIND}
	${USD_SDF}
	${USD_TF}
	${USD_USD}
	${USD_USDGEOM}
	${USD_USDUTILS}
)