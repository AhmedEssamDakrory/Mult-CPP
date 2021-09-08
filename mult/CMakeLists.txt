add_library(mult)

set(HEADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mutex.h
)

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mutex.cpp
)

target_sources(mult
	PUBLIC ${HEADER_FILES}
			${SOURCE_FILES})


