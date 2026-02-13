project("net-utils")

include_directories(include)

file(GLOB SRC src/*.c src/*.cpp src/*.cxx)

add_library(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} ${COMMON_DEPENDENCIES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
  set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 17)
endif()

target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
