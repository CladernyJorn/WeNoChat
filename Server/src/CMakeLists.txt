cmake_minimum_required(VERSION 3.22)
project(Server)

set(PRJ_EXE ${PROJECT_NAME})

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR} CPP_FILES)

find_library(SQLITE3_LIB sqlite3)

add_executable(${PRJ_EXE} ${CPP_FILES})
target_link_libraries(${PRJ_EXE} ${SQLITE3_LIB})

install(TARGETS ${PRJ_EXE} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
