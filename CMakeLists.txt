cmake_minimum_required(VERSION 4.2.0)
project(FileStatTool)  # 项目名称
set(CMAKE_CXX_STANDARD 11)  # 指定C++11标准
add_executable(file_stat main.cpp wordcount.cpp) 