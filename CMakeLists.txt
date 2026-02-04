# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
#
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("network-dev")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../dist/bin)

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

add_subdirectory ("libs")
add_subdirectory ("apps")
