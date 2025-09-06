add_library(json)

# Add include directories for header files
target_include_directories(json PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cJSON
)

# Find all .c files in the current directory
file(GLOB JSON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/cJSON/cJSON_Utils.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cJSON/cJSON.c
)

target_sources(json PRIVATE
    ${JSON_SOURCES}
)

# Link against the component other libraries if needed
# target_link_libraries(json PUBLIC component)

target_compile_options(json PRIVATE
    -g
    # $<$<COMPILE_LANGUAGE:C,CXX>:-include${PROJECT_SOURCE_DIR}/file.h>
)