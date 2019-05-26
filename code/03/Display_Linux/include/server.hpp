#ifndef SERVER_HPP
#define SERVER_HPP
#include "head.hpp"

class recvhandler;
class recvState
{
public:
  //typedef std::shared_ptr<recvState> Ptr;
  virtual int revHead(){return 1;};  //E_OK
  virtual int revCmd(){return 1;};
  virtual int revData(){return 1;};
  virtual int CurrentState(recvhandler *handler){return 1;};
  std::vector<uchar> vec;
  ServerEx *myServerEx;
  static int Msglength;
  static unsigned char Msgbuffer[1024];
protected:
  const unsigned char RECHEAD_SIZE = 4;
  const unsigned char RECCMD_SIZE = 6;
  const unsigned char TYPE_INDEX = 0;
  const unsigned char SUBTYPE_INDEX = 1;
  const unsigned char LEN_INDEX = 2;
  const unsigned int BUFFER_SIZE = 1024;
  bool recv_OK;
};


class recvhandler
{
public:
  recvhandler(recvState *state,ServerEx *myServ) : _recvState(state),_myServ(myServ) {}
  ~recvhandler() { delete _recvState; }
  void SetState(recvState *state)
  {
    delete _recvState;
    _recvState = state;
  }
  int GetState() { return(_recvState->CurrentState(this)); }
  ServerEx *_myServ;
private:
  recvState *_recvState;
  
};

class revHeadState : public recvState
{
public:
  revHeadState(ServerEx * serv);
  ~revHeadState(){};
  int revHead(recvhandler *handler);
  int CurrentState(recvhandler *handler);
  ServerEx* myServerEx;
private:
  
};

class revCmdState : public recvState
{
public:
  revCmdState(ServerEx * serv);
  int revCmd(recvhandler *handler);
  int CurrentState(recvhandler *handler);
};

class revDataState : public recvState
{
public:
  revDataState(ServerEx * serv);
  int revData(recvhandler *handler);
  int CurrentState(recvhandler *handler);
};

class baseServer
{
public:
  enum status
  {
    E_OK = 1,
    E_NOK = -1
  };
  baseServer();
  ~baseServer(){};
  int socketCreate(int type, int way, int ip, int port);
  int socketBind(void);
  int socketListen(int num);
  int socketAccept(void);
  virtual int socketDataHandler() = 0;
  int socketDisconnect(void);
  int socketCloseServer(void);
  int getConnectfd(void);

private:
  int serverfd, connectfd;
  struct sockaddr_in serveraddr;
};
#if 0
class mySelect
{
public:
  fd_set read_fds;  //读文件操作符
  mySelect(){FD_ZERO(&read_fds);};
  void select_set(ServerEx* serv);
  int select_find(ServerEx* serv);
}
#endif
class mylock;
class ServerEx : public baseServer
{
public:
  //typedef std::shared_ptr<ServerEx> Ptr;
  ServerEx(display* disp);
  ~ServerEx(){};
  void sendBeatCmd();
  void sendTrans(bool cmd);
  int socketDataHandler();
  int ReceiveDataFrame();
  int socketSendBeatFrame(uchar *cmdFrame);
  int socketSendCmdFrame(uchar *cmdFrame);
  void select_zero();
  void select_set();
  void select_clr();
  int select_iset();
  int myselect();
  void BeatDetect();
  int getBeat();
  void resetBeat();
  recvState *_myRecv;
  cv::Mat Img;
  bool revOK;
  int page;
private:
  int sendCmd, sendSubCmd;
  uchar cmdBuff[10];
  mylock *_mylock;
  int beat; /* keep alive signal with every 1s */
  bool once;
  fd_set read_fds; 
  struct timeval tv;
};
#endif