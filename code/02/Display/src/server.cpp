#include "server.hpp"
using namespace std;

int recvState::Msglength = 0;
unsigned char recvState::Msgbuffer[1024] = {0};
int ServerEx::getBeat(void)
{
  return (this->beat);
}

void ServerEx::resetBeat(void)
{
  this->_mylock->startLock();
  this->beat = ctrl::typeMain::transData;
  this->_mylock->stopLock();
}

void ServerEx::BeatDetect()
{
  static int cnt = 0;
  while (1)
  {
    Sleep(100);
    cnt++;
    if (cnt >= 10)
    {
      this->_mylock->startLock();
      this->beat = ctrl::typeMain::beat;
      this->_mylock->stopLock();
      cnt = 0;
#if (MYDEBUG == TRUE)
      std::cout << "timer is up,beat=" <<this->beat <<std::endl;
#endif
    }
  }
}
revHeadState::revHeadState(ServerEx *serv)
{
  this->myServerEx = serv;
}
void revHeadState::revHead(recvhandler *handler)
{
  uchar msg_head[RECHEAD_SIZE] = {0};
  int len, ret = 0;
  memset(msg_head, 0, RECHEAD_SIZE);
  len = recv(this->myServerEx->getConnectfd(), (char *)msg_head, RECHEAD_SIZE, MSG_WAITALL);
  if (ret < 0)
  {
    cout << "exit1" << endl;
    closesocket(this->myServerEx->getConnectfd());
  }
  //cout << "recv len=" << len << endl;
  if ((len == SOCKET_ERROR) || (len == 0))
  {
    this->recv_OK = FALSE;
  }
  else
  {
    if ((msg_head[0] == 0xA5) &&
        (msg_head[1] == 0xA5) &&
        (msg_head[2] == 0xA5) &&
        (msg_head[3] == 0xff))
    {
      this->recv_OK = TRUE;
      handler->SetState(new revCmdState(handler->_myServ));
      handler->GetState();
    }
    else
    {
      this->recv_OK = FALSE;
    }
  }
}

void revHeadState::CurrentState(recvhandler *handler)
{
  revHead(handler);
}
revCmdState::revCmdState(ServerEx *serv)
{
  this->myServerEx = serv;
}
void revCmdState::revCmd(recvhandler *handler)
{
  uchar msg_cmd[RECCMD_SIZE] = {0};
  int len, ret = 0;
  memset(msg_cmd, 0, RECCMD_SIZE);
  len = recv(this->myServerEx->getConnectfd(), (char *)msg_cmd, RECCMD_SIZE, MSG_WAITALL);
  if (ret < 0)
  {
    cout << "exit2" << endl;
    closesocket(this->myServerEx->getConnectfd());
  }
  if ((len == SOCKET_ERROR) || (len == 0))
  {
    this->recv_OK = FALSE;
  }
  else
  {
    if ((msg_cmd[TYPE_INDEX] == ctrl::typeMain::transData) &&
        (msg_cmd[SUBTYPE_INDEX] == ctrl::typeSubMain::disable))
    {

      this->Msglength = ((msg_cmd[LEN_INDEX] << 24) & (0xFF000000)) |
                        ((msg_cmd[LEN_INDEX + 1] << 16) & (0xFF0000)) |
                        ((msg_cmd[LEN_INDEX + 2] << 8) & (0xFF00)) |
                        ((msg_cmd[LEN_INDEX + 3]) & (0xFF));
      //cout<<"server:rec length:"<<this->Msglength<<endl;
      handler->SetState(new revDataState(handler->_myServ));
      handler->GetState();
    }
    else
    {
      this->recv_OK = FALSE;
    }
  }
}

void revCmdState::CurrentState(recvhandler *handler)
{
  revCmd(handler);
}
revDataState::revDataState(ServerEx *serv)
{
  this->myServerEx = serv;
}
void revDataState::revData(recvhandler *handler)
{
  int size = 0;
  handler->_myServ->revOK = FALSE;
  //cout<<"server:revData length:"<<srecvState.Msg.length<<endl;
  while (this->Msglength > 0)
  {
    size = recv(this->myServerEx->getConnectfd(), (char *)&this->Msgbuffer[0], BUFFER_SIZE, 0);
    if (size < 0)
    {
      cout << "exit3" << endl;
      closesocket(this->myServerEx->getConnectfd());
    }
    for (int i = 0; i < size; i++)
    {
      this->vec.push_back(this->Msgbuffer[i]);
    }
    this->Msglength = this->Msglength - size;
    //cout<<"size="<<size<<endl;
    //cout<<"length="<<this->Msglength<<endl;
  }

  handler->_myServ->Img = cv::imdecode(this->vec, CV_LOAD_IMAGE_COLOR);
  this->vec.clear();
  std::vector<uchar>(this->vec).swap(this->vec);
  handler->_myServ->revOK = TRUE;
}

void revDataState::CurrentState(recvhandler *handler)
{
  revData(handler);
}

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

  memset(&(this->serveraddr), 0, sizeof(this->serveraddr));
  this->serveraddr.sin_family = type; //AF_INET;
  this->serveraddr.sin_addr.s_addr = htonl(ip);
  this->serveraddr.sin_port = htons(port);
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
  //cout << "baseServer connectfd=" << this->connectfd << endl;
  if (this->connectfd == -1)
  {
    ret = E_NOK;
    cout << "accept failed!" << endl;
    exit(0);
  }
  return (ret);
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
}
int baseServer::getConnectfd(void)
{
  return (this->connectfd);
}
ServerEx::ServerEx(display *disp)
{
  disp->_myServerEx = this;
  this->revOK = FALSE;
  this->beat = ctrl::typeMain::transData;
  this->once = 0;
#ifdef MINGW32
  WSADATA wsadata;
  if (WSAStartup(MAKEWORD(1, 1), &wsadata) == SOCKET_ERROR)
  {
    printf("WSAStartup() fail\n");
    exit(0);
  }
#endif
  this->cmdBuff[0] = 0xA5;
  this->cmdBuff[1] = 0xA5;
  this->cmdBuff[2] = 0xA5;
  this->cmdBuff[3] = 0xFF;
  this->cmdBuff[4] = 0x01;
  this->cmdBuff[5] = 0x01;
  this->cmdBuff[6] = 0x0;
  this->cmdBuff[7] = 0x0;
  this->cmdBuff[8] = 0x0;
  this->cmdBuff[9] = 0x0;
}
void ServerEx::sendTrans(bool cmd)
{
  this->sendSubCmd = cmd;
}

void ServerEx::sendBeatCmd()
{
  this->_mylock->startLockCmd();
  this->sendCmd = ctrl::typeMain::beat;
  this->_mylock->stopLockCmd();
}

int ServerEx::ReceiveDataFrame()
{
  recvhandler *handler = new recvhandler(new revHeadState(this), this);
  handler->GetState();
  return (0);
}
int ServerEx::socketSendBeatFrame(uchar *cmdFrame)
{
  int ret = 0;
  ret = send(getConnectfd(), (char *)cmdFrame, 10, 0);
  if (ret < 0)
  {
    cout << "exit4" << endl;
    closesocket(getConnectfd());
  }
  return (0);
}
int ServerEx::socketSendCmdFrame(uchar *cmdFrame)
{
  int ret = 0;

  if(this->sendSubCmd == ctrl::typeSubMain::enable)
  {
    this->once = 0;
    cmdFrame[5]=1;
    ret = send(getConnectfd(), (char *)cmdFrame, 10, 0);
    if (ret < 0)
    {
      cout << "exit4" << endl;
      closesocket(getConnectfd());
    }
    ReceiveDataFrame();
  }
  else
  {
    if (once == 0) /* add once to reduce busload */
    {
      cmdFrame[5]=0;
      ret = send(getConnectfd(), (char *)cmdFrame, 10, 0);
      if (ret < 0)
      {
        cout << "exit4.1" << endl;
        closesocket(getConnectfd());
      }
      once = 1;
    }
  }

  return (0);
}

int ServerEx::socketDataHandler()
{
  while (1)
  {
    if (sendCmd == ctrl::typeMain::beat)
    {
      this->_mylock->startLockCmd();
      sendCmd = ctrl::typeMain::transData;
      this->_mylock->stopLockCmd();

      cmdBuff[4] = ctrl::typeMain::beat;
      socketSendBeatFrame(&this->cmdBuff[0]);
    }
    else
    { /* normal */
      cmdBuff[4] = ctrl::typeMain::transData;
      socketSendCmdFrame(&this->cmdBuff[0]);
    }
  }
  return (0);
}
