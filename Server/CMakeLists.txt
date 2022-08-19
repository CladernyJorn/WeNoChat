cmake_minimum_required(VERSION 3.22)
project(Server)

find_library(SQLITE3_LIB sqlite3)
# find_library(JSONCPP_LIB jsoncpp)

set(PRJ_EXE ${PROJECT_NAME})
set(PRJ_LIBS ${SQLITE3_LIB})

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/json JSON_CPP_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/Server SERVER_CPP_FILES)

set(CPP_FILES ${JSON_CPP_FILES} ${SERVER_CPP_FILES} ${PROJECT_SOURCE_DIR}/main.cpp)

add_executable(${PRJ_EXE} ${CPP_FILES})
target_link_libraries(${PRJ_EXE} ${PRJ_LIBS})

install(TARGETS ${PRJ_EXE} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
