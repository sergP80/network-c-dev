project("thread-utils")

# Include FetchContent
include(FetchContent)

# Fetch tinycthread
FetchContent_Declare(
        tinycthread
        GIT_REPOSITORY https://github.com/tinycthread/tinycthread.git
        GIT_TAG        master
)

FetchContent_MakeAvailable(tinycthread)

file(GLOB SRC ${tinycthread_SOURCE_DIR}/source/*.c ${tinycthread_SOURCE_DIR}/source/*.cpp ${tinycthread_SOURCE_DIR}/source/*.cxx)

add_library(${PROJECT_NAME} ${SRC})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
  set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 17)
endif()

target_include_directories(${PROJECT_NAME} INTERFACE ${tinycthread_SOURCE_DIR}/source)

if(APPLE OR UNIX)
  find_package(Threads REQUIRED)
  target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
endif()