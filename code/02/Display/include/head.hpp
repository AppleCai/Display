#ifndef HEAD_HPP
#define HEAD_HPP

#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <winsock2.h>
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

#define MINGW32
#define MYDEBUG FALSE//TRUE

#define error_Log(a)  std::cout<<a<<std::endl;
#define debug_Log(a)  std::cout<<a<<std::endl;
#endif 
