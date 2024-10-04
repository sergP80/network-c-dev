project("thread-utils")

include_directories(include)

# Include FetchContent
include(FetchContent)

# Fetch tinycthread
FetchContent_Declare(
        tinycthread
        GIT_REPOSITORY https://github.com/tinycthread/tinycthread.git
        GIT_TAG        master
)

FetchContent_Declare(
        c_threadpool
        GIT_REPOSITORY https://github.com/Pithikos/C-Thread-Pool.git
        GIT_TAG        master
)

FetchContent_MakeAvailable(tinycthread c_threadpool)

file(GLOB SRC ${tinycthread_SOURCE_DIR}/source/*.c ${c_threadpool_SOURCE_DIR}/*.c)

add_library(${PROJECT_NAME} ${SRC}
        include/thread-utils.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
  set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 17)
endif()

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${tinycthread_SOURCE_DIR}/source
        ${c_threadpool_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/include
)

if(APPLE OR UNIX)
  find_package(Threads REQUIRED)
  target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
endif()