cmake_minimum_required (VERSION 3.10)

project ("network-dev")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist/bin)


find_package(Git REQUIRED)

if(Git_FOUND)
    message(STATUS "Git found: ${GIT_EXECUTABLE}")

    # Example of retrieving the latest commit hash
    execute_process(
        COMMAND ${GIT_EXECUTABLE} log -n 1 HEAD "--pretty=format:%h"
        OUTPUT_VARIABLE git_hash
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    message(STATUS "Current Git commit hash: ${git_hash}")
else()
    message(FATAL_ERROR "Could not locate Git. Please install it to continue.")
endif()

include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)

FetchContent_MakeAvailable(googletest)

set(GTEST_INCLUDE_DIR ${googletest_SOURCE_DIR}/include)

list(APPEND GTEST_COMMON_DEPS gtest gtest_main)

# Enable testing
enable_testing()

FetchContent_Declare(
        cthreadpool
        GIT_REPOSITORY https://github.com/sergP80/c-thread-pool.git
)

FetchContent_MakeAvailable(cthreadpool)

set(C_THREAD_POOL_INCLUDE_DIR ${cthreadpool_SOURCE_DIR}/include)

if(WIN32)
  LIST(APPEND COMMON_DEPENDENCIES wsock32 ws2_32)
else()
  LIST(APPEND COMMON_DEPENDENCIES pthread m)
endif()

add_subdirectory ("libs")
add_subdirectory ("apps")
