project("square-root-server-mp2")

include_directories(include)

file(GLOB SRC src/*.c src/*.cpp src/*.cxx)

add_executable (${PROJECT_NAME} ${SRC})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
  set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 17)
endif()

target_link_libraries(${PROJECT_NAME} ${COMMON_DEPENDENCIES} ${SHARED_LIBS} "tcp-server-mp")
