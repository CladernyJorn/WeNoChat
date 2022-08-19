cmake_minimum_required(VERSION 3.22)
project(Server)

set(PRJ_EXE ${PROJECT_NAME})

find_package(sqlite3, REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR} CPP_FILES)

add_executable(${PRJ_EXE} ${CPP_FILES})

install(TARGETS ${PRJ_EXE} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
