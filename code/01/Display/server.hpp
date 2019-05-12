#ifndef SERVER_HPP
#define SERVER_HPP
#include "key.hpp"
#include "head.hpp"

#define BUFFER_SIZE 1024

/* socket通信基类 */
class baseServer
{
public:
  enum status
  {
    E_OK = 0,
    E_NOK = -1
  };
  baseServer();
  ~baseServer(){};
  int socketCreate(int type, int way, int ip, int port);
  int socketBind(void);
  int socketListen(int num);
  int socketAccept(void);
  //virtua void socketDataHandler(void);
  virtual void socketDataHandler() = 0;
  int socketDisconnect(void);
  int socketCloseServer(void);
  int getConnectfd(void);

private:
  int serverfd, connectfd;
  struct sockaddr_in serveraddr;
};

/* socket通信继承类 */
class ServerEx : public baseServer
{
public:
  ServerEx();
  ~ServerEx(){};
  void socketDataHandler();
  void ReceiveFrame();
  void DisplayFrame();
  void HMIControlStrategy(char cmd);
  cv::Mat &GetImg();
  void server();

private:
  struct _Msg
  {
    int length = 0;
    unsigned char cokstart[1] = {0};
    unsigned char buffer[BUFFER_SIZE];
  } Msg;
  std::vector<uchar> vec;
  cv::Mat img_decode;
};

/* 策略模式：用于按键对HMI显示的控制策略 */
class myLock;
class HMICtrl
{
public:
  HMICtrl() : _en(TRUE){};
  ~HMICtrl(){};
  void transmitCtrl();
  void transmitCtrlCfg(bool en);
  bool getTransmitCtrlCfg();
  void FrameTerminal();
  virtual void ActionInterface() = 0;
  ServerEx *myServerEx;
protected:
  myLock *keylock;
private:
  bool _en;
};
class keysearch;
class HMICtrlEnable : public HMICtrl
{
public:
  HMICtrlEnable(keysearch *keysearch) : _cmd('j'), _keysearch(keysearch){};
  ~HMICtrlEnable(){};
  virtual void ActionInterface();

private:
  char _cmd;
  keysearch *_keysearch;
};

class HMICtrlDisable : public HMICtrl
{
public:
  HMICtrlDisable(){};
  ~HMICtrlDisable(){};
  virtual void ActionInterface();
};

class Context
{
public:
  Context(HMICtrl *hmiCtrl);
  ~Context();
  void HMIcontrol();

private:
  HMICtrl *_HMICtrl;
};

#endif