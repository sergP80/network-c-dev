project("square-root-server-mt")

include_directories(${C_THREAD_POOL_INCLUDE_DIR} include)

file(GLOB SRC src/*.c src/*.cpp src/*.cxx)

add_executable (${PROJECT_NAME} ${SRC})

target_link_directories(${PROJECT_NAME} PRIVATE
  "${CMAKE_BINARY_DIR}/../dist/lib"
)

target_link_libraries(${PROJECT_NAME} ${COMMON_DEPENDENCIES} ${SHARED_LIBS} c_thread_pool)
