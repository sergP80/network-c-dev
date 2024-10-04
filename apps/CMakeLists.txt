if(WIN32)
	set(COMMON_DEPENDENCIES wsock32 ws2_32)
endif()

set(SHARED_LIBS net-utils thread-utils shared-data)
add_subdirectory("ns-lookup")
add_subdirectory("tcp")