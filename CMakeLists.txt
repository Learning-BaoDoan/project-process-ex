cmake_minimum_required(VERSION 3.12.4)

# Set project name
set(PROJECT_TOOLNAME "BA200")
set(PROJECT_VERSION_MAJOR "24")
set(PROJECT_VERSION_MINOR "00")
set(PROJECT_VERSION_PATCH "05")
set(PROJECT_PRODUCT_ID "0x0431")
string(TIMESTAMP BUILD_TIME "%b%d%y")
set(FIRMWARE_BUILDNO "RC03")
set(PROJECT_VERSION "V${PROJECT_VERSION_MAJOR}_${PROJECT_VERSION_MINOR}_${PROJECT_VERSION_PATCH}")
set(PROJECT_VER "V${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
set(PROJECT_AUTHOR "Bao Doan")

if(PRE_TEST_FIRMWARE)
    message(STATUS "Pre-test Firmware")
    set(PROJECT_BIN "M_${PROJECT_VER}_${PROJECT_TOOLNAME}_${PROJECT_PRODUCT_ID}_${BUILD_TIME}_${FIRMWARE_BUILDNO}")
else()
    message(STATUS "Release Firmware")
    set(PROJECT_BIN "M_${PROJECT_VER}_${PROJECT_TOOLNAME}_${PROJECT_PRODUCT_ID}_${BUILD_TIME}")
endif()

# After defining variables
message(STATUS "Building Firmware")
message(STATUS "Project Toolname: ${PROJECT_TOOLNAME}")
message(STATUS "Product ID: ${PROJECT_PRODUCT_ID}")
message(STATUS "Build Time: ${BUILD_TIME}")

if(PRE_TEST_FIRMWARE)
    message(STATUS "Project Version: ${PROJECT_VER}_${FIRMWARE_BUILDNO}")
else()
    message(STATUS "Project Version: ${PROJECT_VER}")
endif()
message(STATUS "Project Binary Name: ${PROJECT_BIN}")

project(${PROJECT_BIN})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# Set C and C++ standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

# Add header file
include_directories(${PROJECT_SOURCE_DIR}/)

add_executable(${PROJECT_BIN}
    ${PROJECT_SOURCE_DIR}/main.c

    # Add source files in here.
)

# Add component
add_subdirectory(middlewares/libs_3rd/json)
target_link_libraries(${PROJECT_BIN} PRIVATE json)

# Custom target to run the executable
add_custom_target(run COMMAND ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_BIN} DEPENDS ${PROJECT_BIN})