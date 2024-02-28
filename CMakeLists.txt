cmake_minimum_required(VERSION 3.5)
project(cmc)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include directories
include_directories(include)

add_subdirectory(Chess-Library)
include_directories(Chess-Library)


set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB SOURCES ${SRC_DIR}/*.cpp)

set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
file(GLOB TESTS ${SRC_DIR}/*.cpp)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB HEADERS ${INCLUDE_DIR}/*.h ${INCLUDE_DIR}/*.hpp)

# Add an executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${TESTS})

target_link_libraries(${PROJECT_NAME} ChessLibrary)

# Add any additional libraries or dependencies
# Example:
# find_package(OpenCV REQUIRED)
# target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# Set compiler flags (optional)
# Example:
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)

# Set output directory (optional)
# Example:
# set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

