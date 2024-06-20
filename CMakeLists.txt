cmake_minimum_required(VERSION 3.21)

# Project name
project(MySort VERSION 0.1)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Set the target name and Add executable
set(TARGET_NAME mysort)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/TestPattern/*.cpp)
add_executable(${TARGET_NAME} ${SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# 2. If the build type is not specified, set it to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 3. Set the build type-specific compile definitions
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${TARGET_NAME} PRIVATE RELEASE_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${TARGET_NAME} PRIVATE DEBUG_BUILD)
endif()

# 4. Set the compiler-specific options
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

# 5.Set target include directories
target_include_directories(
    ${TARGET_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/Yutils/include
)

# 6.1. Get Yutils library path
if (SHARED_YUTILS)
    target_compile_definitions(${TARGET_NAME} PRIVATE YUTILS_IMPORT)
    if (WIN32 OR WIN64)
        set(YUTILS_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/Yutils.dll)
    else()
        set(YUTILS_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/Yutils.so)
    endif()
else()
    if (WIN32 OR WIN64)
        set(YUTILS_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/Yutils.lib)
    else()
        set(YUTILS_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/Yutils.a)
    endif()
endif()
message(STATUS "Yutils library path: ${YUTILS_LIB_PATH}")

# 6.2. Link to Yutils library
target_link_libraries(
    ${TARGET_NAME} PRIVATE
    ${YUTILS_LIB_PATH}
)

# 7. Set output directory
set_target_properties(
    ${TARGET_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}
)

