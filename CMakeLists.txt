cmake_minimum_required (VERSION 3.1)

project(qzjw-cpp-sdk)

set(CMAKE_CXX_STANDARD 11)

find_package(nlohmann_json CONFIG REQUIRED)

add_subdirectory(CURLWrapper)

aux_source_directory(./src SRCS)

add_library(${PROJECT_NAME} STATIC ${SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PRIVATE CURLWrapper)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

add_subdirectory(examples)