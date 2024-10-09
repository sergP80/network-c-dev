if(WIN32)
	set(COMMON_DEPENDENCIES wsock32 ws2_32)
else()
	set(COMMON_DEPENDENCIES pthread m)
endif()

set(SHARED_LIBS net-utils thread-utils shared-data)
add_subdirectory("ns-lookup")
add_subdirectory("tcp")