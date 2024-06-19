cmake_minimum_required(VERSION 3.21)

# Project name
project(MySort VERSION 0.1)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set defaut build type to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DRELEASE_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG_BUILD)
endif()

if(MSVC)
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
    # MSVC compiler-specific options
    add_compile_options(/permissive- /Zc:forScope)
else()
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

# Get source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/TestPattern/*.cpp)

add_executable(mysort ${SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Set target include directories:
# - MySort/include
# - MySort/vendor/Yutils/include
target_include_directories(
    mysort PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Yutils/include
)

target_link_libraries(
    mysort PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/libYutils.a
)

# Set output dir
set_target_properties(
    mysort PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}
)

# If shared library is set
if (SHARED_YUTILS)
    target_compile_definitions(mysort PRIVATE YUTILS_IMPORT)
endif()