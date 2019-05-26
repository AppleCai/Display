# 声明要求的 cmake 最低版本
cmake_minimum_required( VERSION 2.8 )

# 声明一个 cmake 工程
PROJECT(Pthread_test CXX)
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
# 设置编译模式
set( CMAKE_BUILD_TYPE "Debug" )
#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 " )
add_compile_options(-std=c++11)

include_directories( "D:/opencv341/VScodebuild/install/include" )
link_directories("D:\\opencv341\\VScodebuild\\install\\x86\\mingw\\bin")
add_executable( main main.cpp)
target_link_libraries(main ws2_32 -lopencv_core341 -lopencv_imgcodecs341 -lopencv_highgui341)
