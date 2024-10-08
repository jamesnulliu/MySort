cmake_minimum_required(VERSION 3.21)

# Create Project
project(MySort VERSION 0.1)

# ==================================================================================================
# Compiler and Linker Configuration
# --------------------------------------------------------------------------------------------------
# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(STACK_SIZE 268435456)
# MSVC
if(MSVC AND WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Zi")
    add_compile_options(/permissive- /Zc:forScope)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:${STACK_SIZE}")
# Clang
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    if(WIN32)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,/STACK:${STACK_SIZE}")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-zstack-size=${STACK_SIZE}")
    endif()
# GCC
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Set different compile options for Release and Debug modes
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    if(WIN32)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,${STACK_SIZE}")
    else()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-zstack-size=${STACK_SIZE}")
    endif()
else()
    message(FATAL_ERROR "Unsupported compiler")
endif()
# ==================================================================================================

# ==================================================================================================
# Target Configuration
# --------------------------------------------------------------------------------------------------
# Set the Target Name and Add Executable
set(TARGET_NAME mysort)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(${TARGET_NAME} ${SOURCES})

# Specify Build Type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Define Macros According to Build Type
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${TARGET_NAME} PRIVATE RELEASE_BUILD)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${TARGET_NAME} PRIVATE DEBUG_BUILD)
endif()

# Include MySort Header Files
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Install Yutils Library ---------------------------------------------------------------------------
add_subdirectory("vendor/Yutils")

# Link Yutils Library
target_link_libraries(${TARGET_NAME} PRIVATE Yutils::Yutils)

# Set Binary Output Path
if(NOT DEFINED OUTPUT_DIR)
    set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif()
set_target_properties(
    ${TARGET_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY 
    ${OUTPUT_DIR}/bin/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}
)
# ==================================================================================================