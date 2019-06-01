#ifndef HEAD_HPP
#define HEAD_HPP

//#define MINGW32

#include <stdio.h>
#include <sys/types.h>
#include <error.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <iostream>
#include <opencv2/opencv.hpp>
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

#define PATHNAME "/tmp"
#define PROJ_ID    888
#define PROJ_IDMsg  891
#define MYSIZE   530432  //size for shared memory=518K
#define MYGROUP  1
#define KEYGROUP 2
#define error_Log(a)  std::cout<<a<<std::endl;
#define debug_Log(a)  std::cout<<a<<std::endl;
#endif 
