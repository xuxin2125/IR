cmake_minimum_required(VERSION 3.6)
project(IR_Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/IndexList.cpp src/IndexList.h src/ItemInfo.h src/Utils.cpp src/Utils.h src/Query.cpp src/Query.h src/VSM.cpp src/VSM.h)
add_executable(IR_Project ${SOURCE_FILES})