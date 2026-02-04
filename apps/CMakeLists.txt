if(WIN32)
	LIST(APPEND COMMON_DEPENDENCIES wsock32 ws2_32)
else()
	LIST(APPEND COMMON_DEPENDENCIES pthread m)
endif()

set(SHARED_LIBS net-utils shared-data)

add_subdirectory("ns-lookup")
add_subdirectory("tcp")