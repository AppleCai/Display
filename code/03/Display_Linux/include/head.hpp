#ifndef HEAD_HPP
#define HEAD_HPP

//#define MINGW32

#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#if defined(MINGW32)
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <string>
#include <vector>
#include <condition_variable>
#include "cfg.hpp"
#include "ctrl.hpp"
#include "display.hpp"
#include "HMI.hpp"
#include "key.hpp"
#include "lock.hpp"
#include "server.hpp"

#define TRUE    1
#define FALSE   0
#define MYDEBUG FALSE//TRUE
#if defined(MINGW32)
#else
#define SOCKET_ERROR  -1
#endif
#define error_Log(a)  std::cout<<a<<std::endl;
#define debug_Log(a)  std::cout<<a<<std::endl;
#endif 
