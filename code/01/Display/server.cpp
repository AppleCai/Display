#include "server.hpp"
#include "key.hpp"
using namespace std;
//HMICtrlDisable sHMICtrl;
HMICtrlEnable sHMICtrl(&k);
cv::Mat &ServerEx::GetImg()
{
  return (img_decode);
}

ServerEx::ServerEx()
{
  sHMICtrl.myServerEx = this; /*register here*/
}
/* HMI控制策略 */
void HMICtrl::transmitCtrlCfg(bool en)
{
  this->_en = en;
}

bool HMICtrl::getTransmitCtrlCfg()
{
  return (this->_en);
}

void HMICtrl::FrameTerminal()
{
  char cok[1] = {0x55};
  send(sHMICtrl.myServerEx->getConnectfd(), cok, 1, 0);
  //send(this->myServerEx->getConnectfd(), cok, 1, 0);
}

void HMICtrl::transmitCtrl()
{
  if (this->getTransmitCtrlCfg() == TRUE)
  {
    this->keylock->startLock();
    this->keylock->waitEvent();
  }
  FrameTerminal();
}

void HMICtrlEnable::ActionInterface()
{
  if ((this->_keysearch->getJumpInfo()) == 1)
  {
    #if (MYDEBUG == TRUE)
    cout << "jump" << endl;
    #endif
  }
  else
  {
    cv::imshow("pic", sHMICtrl.myServerEx->GetImg());
    //cv::imshow("pic", this->myServerEx->GetImg());
    cv::waitKey(1);
  }
  this->transmitCtrl();
}

void HMICtrlDisable::ActionInterface()
{
  cv::imshow("pic", sHMICtrl.myServerEx->GetImg());
  //cv::imshow("pic", this->myServerEx->GetImg());
  cv::waitKey(1);
  this->transmitCtrl();
}

Context::Context(HMICtrl *hmiCtrl)
{
  this->_HMICtrl = hmiCtrl;
}

Context::~Context()
{
  delete this->_HMICtrl;
}

void Context::HMIcontrol()
{
  /* set transmit control,use 's' */
  this->_HMICtrl->transmitCtrlCfg(TRUE);
  this->_HMICtrl->ActionInterface();
}

/* socket server 设置 */
int baseServer::socketCreate(int type, int selection, int ip, int port)
{
  int ret = E_OK;
  this->serverfd = socket(type, selection, 0);
  if (this->serverfd == -1)
  {
    ret = E_NOK;
    cout << "accept failed!" << endl;
    exit(0);
  }
  //CO_E_NOCOOKIES清零
  memset(&(this->serveraddr), 0, sizeof(this->serveraddr));
  //设置协议
  this->serveraddr.sin_family = type; //AF_INET;
  //设置IP
  this->serveraddr.sin_addr.s_addr = htonl(ip); //htonl(INADDR_ANY);
  //设置Port
  this->serveraddr.sin_port = htons(port); //htons(1024);
  return (ret);
}

int baseServer::socketBind(void)
{
  int ret = E_OK;
  ret = bind(this->serverfd, (struct sockaddr *)&(this->serveraddr), sizeof(this->serveraddr));
  if (ret == -1)
  {
    cout << "bind failed!" << endl;
    exit(0);
  }
  return (ret);
}

int baseServer::socketListen(int num)
{
  int ret = E_OK;
  ret = listen(this->serverfd, num);
  if (ret == -1)
  {
    cout << "listen failed!" << endl;
    exit(0);
  }
  return (ret);
}

int baseServer::socketAccept(void)
{
  int ret = E_OK;
  this->connectfd = accept(this->serverfd, (struct sockaddr *)NULL, NULL);
  if (this->connectfd == -1)
  {
    ret = E_NOK;
    cout << "accept failed!" << endl;
    exit(0);
  }
  return (ret);
}

int baseServer::getConnectfd(void)
{
  return (this->connectfd);
}

int baseServer::socketDisconnect(void)
{
  int ret = E_OK;
  ret = closesocket(this->connectfd);
  if (ret == -1)
  {
    cout << "closesocket failed!" << endl;
    exit(0);
  }
  return (ret);
}

int baseServer::socketCloseServer(void)
{
  int ret = E_OK;
  ret = closesocket(this->serverfd);
  if (ret == -1)
  {
    cout << "socketCloseServer failed!" << endl;
    exit(0);
  }
  return (ret);
}

baseServer::baseServer()
{
#ifdef MINGW32
  //Winsows下启用socket
  WSADATA wsadata;
  if (WSAStartup(MAKEWORD(1, 1), &wsadata) == SOCKET_ERROR)
  {
    printf("WSAStartup() fail\n");
    exit(0);
  }
#endif
  this->serveraddr.sin_family = AF_INET;
  this->serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  this->serveraddr.sin_port = htons(1024);
  this->serverfd = socket(AF_INET, SOCK_STREAM, 0);
  this->connectfd = 0;
}

/* data handler */
void ServerEx::ReceiveFrame()
{
  int size = 0;
  recv(getConnectfd(), (char *)&Msg.buffer[0], 4, 0);
  Msg.length = ((Msg.buffer[1] << 16) & (0xFF0000)) | ((Msg.buffer[2] << 8) & (0xFF00)) | ((Msg.buffer[3]) & (0xFF));
  if (Msg.length > 0)
  {
    // TODO: check if delete the head of 0x33, what will happen.
    Msg.cokstart[0] = 0x33;
    send(getConnectfd(), (char *)&Msg.cokstart[0], 1, 0);
  }
  #if (MYDEBUG == TRUE)
  std::cout<<length<<std::endl;
  #endif
  while (Msg.length > 0)
  {
    size = recv(getConnectfd(), (char *)&Msg.buffer[0], BUFFER_SIZE, 0);
    for (int i = 0; i < size; i++)
    {
      vec.push_back(Msg.buffer[i]);
    }
    Msg.length = Msg.length - size;
  }
}

void ServerEx::DisplayFrame()
{
  this->img_decode = cv::imdecode(this->vec, CV_LOAD_IMAGE_COLOR);
  vec.clear();
  std::vector<uchar>(vec).swap(vec);
  // TODO: shall add key configuration
  HMIControlStrategy('j');
}

void ServerEx::socketDataHandler(void)
{
  // TODO: shall add stop signal
  for (;;)
  {
    ReceiveFrame();
    DisplayFrame();
  }
}

/* HMI 控制 */
void ServerEx::HMIControlStrategy(char cmd)
{
  // TODO : shall add the function of cmd
  // HMICtrl *pStr = new HMICtrlDisable();
  /* 还要释放堆上的内存太麻烦，做到栈上
  HMICtrl *pStr = new HMICtrlEnable(&k);
  Context *pcon = new Context(pStr);
  pcon->HMIcontrol();*/
  HMICtrlEnable hmictrolEn(&k);
  Context con(&hmictrolEn);
  con.HMIcontrol();
}

void ServerEx::server(void)
{
  ServerEx myserver;
  myserver.socketCreate(AF_INET, SOCK_STREAM, INADDR_ANY, 1024);
  myserver.socketBind();
  myserver.socketListen(2);
  myserver.socketAccept();
  myserver.socketDataHandler();
  myserver.socketDisconnect();
  myserver.socketCloseServer();
}