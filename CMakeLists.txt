# 指定CMake的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(stbProject VERSION 1.0)

# 设置C标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# 添加一个可执行文件
add_executable(MyExecutable main.c)

# 包含stb库的目录，如果stb的头文件在一个特定的目录，你需要指明
# 这里假设 stb 的头文件就在项目根目录下
target_include_directories(MyExecutable PRIVATE ${CMAKE_SOURCE_DIR})