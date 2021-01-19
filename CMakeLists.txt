project(http_gm_server)
cmake_minimum_required(VERSION 3.10)

find_package(nlohmann_json CONFIG REQUIRED)



set(CMAKE_CXX_STANDARD 17)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif(MSVC)

find_package(http_server REQUIRED)
include_directories(${http_server_INCLUDE_DIRS})
FILE(GLOB_RECURSE SRC_LISTS ${CMAKE_SOURCE_DIR}/src/*.cpp )
FILE(GLOB_RECURSE HEADER_LISTS  ${CMAKE_SOURCE_DIR}/src/*.h)

add_executable(${PROJECT_NAME} ${SRC_LISTS} ${HEADER_LISTS})
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json http_server)