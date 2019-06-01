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

class myshm
{
public:
  myshm(ServerEx *serv);
  ~myshm(){};
  int CreateShm();
  char* atAddr();
  int DelAddr(char* shmaddr);
  int DestoryShm();
private:
  int shmid;
};

class mysem
{
public:

union semun
{
  int val;
  struct semid_ds *buf;
  unsigned short int *array;
  struct seminfo * _buf;
};
  mysem(ServerEx *serv);
  ~mysem(){};
  key_t CreateSem(int nums,int keyid);
  void sem_init(int val);
  int sem_get();
  void sem_p();
  void sem_v();
private:
  int semid;
  int semkey;
};

class MYmsg
{
public:
typedef struct{
    int groupID;
    int eventID;
    int buf[4];
}Msg;
MYmsg(ServerEx *serv);
~MYmsg(){};
int CreateMsg();
int IPCsendMsg(Msg * buf);
int IPCrecvMsg(Msg * buf,int type,int wait);
int delMsg();
private:
  int msgid;
};

#endif