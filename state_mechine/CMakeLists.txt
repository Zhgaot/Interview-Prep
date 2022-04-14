# 指定最小cmake版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# 在cmake中使用build.sh中设定好的环境变量来指定编译器位置
SET(CMAKE_C_COMPILER $ENV{GCC_ENV_DIR})
SET(CMAKE_CXX_COMPILER $ENV{GPP_ENV_DIR})

# 设置项目名称
PROJECT(atoi)

# 设置g++编译参数
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

# 指定头文件的包含路径
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

# 指定库生成路径
SET(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# 生成链接库
ADD_LIBRARY(atoi SHARED ./src/atoi.cpp)

# 指定需要链接的库
LINK_LIBRARIES(atoi)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)

# 指定可执行文件的生成路径
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 生成可执行文件
ADD_EXECUTABLE(atoi_test atoi_test.cpp)