add_library(safe_array STATIC)

target_sources(safe_array
    PRIVATE
    safe_array.c
)

target_include_directories(safe_array
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})

add_library(logger STATIC)

target_sources(logger
    PRIVATE
    logger.c
)

target_include_directories(logger
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})