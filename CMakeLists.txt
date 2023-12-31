cmake_minimum_required(VERSION 3.22)
project(explore_rtklib C CXX)

# set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

# enable trace in rtklib
add_definitions(-DTRACE)

# 导入rtklib相关的库与源文件
include_directories(src/include)

file(GLOB SRC_FILES "src/*.c" "src/rcv/*.c" "src/utils/*.c")

# 编译源代码生成库文件
add_library(RTK_LIB ${SRC_FILES})
# 将库文件连接到libblas\liblapack,这几个库都是数学计算库，libz库是解压用的
# windows电脑上没有安装，blas/lapack需要自己手动编译并安装
# target_link_libraries(RTK_LIB blas lapack z)

# 解决undefined reference to `__imp_timeGetTime`的问题
target_link_libraries(RTK_LIB winmm)

# 设置rtklib编译输出的库文件存储到指定目录
set_target_properties(RTK_LIB PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 将运行时生成的可执行文件输出到指定目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 告诉cmake项目存在子目录
add_subdirectory(src)

add_executable(explore_rtklib main.cpp)

# 将本程序连接到rtklib编译生成的静态/动态库
target_link_libraries(explore_rtklib RTK_LIB)

# 导入数学库libm.so不然会出现报错undefined reference to sin/cos之类的
target_link_libraries(explore_rtklib m)
