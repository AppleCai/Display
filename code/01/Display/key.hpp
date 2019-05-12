#ifndef KEY_HPP
#define KEY_HPP

#include "head.hpp"
#include "server.hpp"
extern std::mutex mtx;
extern std::condition_variable event;

class myLock
{
public:
  myLock(){};
  ~myLock(){};
  void startLock();
  void stopLock();
  void waitEvent();
  void eventTrigger();

private:
};

class keysearch
{
public:
  keysearch();
  ~keysearch(){};
  bool getJumpInfo();
  int KeyDetect();
  bool getTransCmd();

private:
  bool jump;
  bool status;
  myLock *keylock;
};
extern keysearch k;

#endif
