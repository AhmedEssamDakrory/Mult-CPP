add_library(mult)

set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mutex.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/thread_pool.h
)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mutex.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/thread_pool.cpp
)

target_sources(mult
	PUBLIC ${HEADER_FILES}
			${SOURCE_FILES})


