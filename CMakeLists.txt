cmake_minimum_required(VERSION 3.10)
project(RepairSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS -static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
# 收集所有源文件
set(SOURCE_FILES
        main.cpp
        header.h
        RepairRecord.cpp
        Date.cpp
        list.cpp
        Date.h
        RepairRecord.h
        list.h
)

set(ICON_RESOURCE ${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.rc)

add_executable(RepairSystem ${SOURCE_FILES} ${ICON_RESOURCE})
