project("square-root-server")

include_directories(include)

file(GLOB SRC src/*.c src/*.cpp src/*.cxx)

add_executable (${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${COMMON_DEPENDENCIES} ${SHARED_LIBS})