#ifndef LOCK_HPP
#define LOCK_HPP
#include "head.hpp"

class mylock
{
public:
  //typedef std::shared_ptr<lock> Ptr;
  mylock(){};
  ~mylock(){};
  void startLock();
  void stopLock();
  void startLockCmd();
  void stopLockCmd();
  void waitEvent();
  void eventTrigger();
private:
};

#endif