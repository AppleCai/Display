# 声明要求的 cmake 最低版本
cmake_minimum_required( VERSION 2.8 )

# 声明一个 cmake 工程
PROJECT(Display_Server CXX)

set( CMAKE_BUILD_TYPE "Debug" )
add_compile_options(-std=c++11)
option(mingw32 "developer in windows" OFF)
message("option is ${mingw32}")

if(mingw32)
	include_directories( "D:/opencv341/VScodebuild/install/include" )
	include_directories(${PROJECT_SOURCE_DIR}/include)
	link_directories("D:\\opencv341\\VScodebuild\\install\\x86\\mingw\\bin")
	#添加src文件夹中的display库
	add_subdirectory(${PROJECT_SOURCE_DIR}/src)
	add_executable( main main.cpp)
	target_link_libraries( main display ws2_32 -lopencv_core341 -lopencv_imgcodecs341 -lopencv_highgui341)
else()
	find_package(OpenCV REQUIRED)
	include_directories(${PROJECT_SOURCE_DIR}/include ${OpenCV_INCLUED_DIRS} )
	#include_directories(${PROJECT_SOURCE_DIR}/include)
	#添加src文件夹中的display库
	add_subdirectory(${PROJECT_SOURCE_DIR}/src)
	add_executable( main main.cpp)
	target_link_libraries( main display ${OpenCV_LIBS})
endif()
