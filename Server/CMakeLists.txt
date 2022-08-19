cmake_minimum_required(VERSION 3.22)
project(Server)

# 第三方库
find_library(SQLITE3_LIB sqlite3)

# 文件名和库名
set(PRJ_EXE ${PROJECT_NAME})
set(PRJ_LIBS ${SQLITE3_LIB})

# 头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 源代码路径
aux_source_directory(${PROJECT_SOURCE_DIR}/json JSON_CPP_FILES)
aux_source_directory(${PROJECT_SOURCE_DIR}/Server SERVER_CPP_FILES)

set(CPP_FILES ${JSON_CPP_FILES} ${SERVER_CPP_FILES} ${PROJECT_SOURCE_DIR}/main.cpp)

# 添加可执行文件
add_executable(${PRJ_EXE} ${CPP_FILES})
target_link_libraries(${PRJ_EXE} ${PRJ_LIBS})

# 安装
install(TARGETS ${PRJ_EXE} RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
