#include "server.hpp"
//using namespace std;
//char mysharebuf[512000]; //500K
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
  while (1)
  {
#if defined(MINGW32)
    Sleep(1000);
#else
    sleep(1);
#endif
    this->_mylock->startLock();
    this->beat = ctrl::typeMain::beat;
    this->_mylock->stopLock();

#if (MYDEBUG == TRUE)
    std::cout << "timer is up,beat=" << this->beat << std::endl;
#endif
  }
}
revHeadState::revHeadState(ServerEx *serv)
{
  this->myServerEx = serv;
}
int revHeadState::revHead(recvhandler *handler)
{
  uchar msg_head[RECHEAD_SIZE];
  int len = 0;
  int ret = baseServer::E_OK;

  this->myServerEx->select_zero();
  this->myServerEx->select_set();
  ret = this->myServerEx->myselect();
  if (ret == -1)
  {
    debug_Log("revHead error data");
    std::cout<<"errno"<<errno<<std::endl;
    return (baseServer::E_NOK);
  }
  else if (ret == 0)
  {
    debug_Log("revHead no data");
    std::cout<<"errno"<<errno<<std::endl;
    
    //timeout error
    this->myServerEx->socketDisconnect();
    //close(this->myServerEx->getConnectfd());
    return(baseServer::E_NOK);
    //replay
    //handler->SetState(new revHeadState(handler->_myServ));
    //ret = handler->GetState();
  }
  else
  {
    if (this->myServerEx->select_iset())
    {
      memset(msg_head, 0, RECHEAD_SIZE);
      len = recv(this->myServerEx->getConnectfd(), (char *)msg_head, RECHEAD_SIZE, MSG_WAITALL);
      //cout << "recv len=" << len << endl;
      if ((len == SOCKET_ERROR) || (len == 0))
      {
        this->recv_OK = FALSE;
        std::cout << "exit1" << std::endl;
#if defined(MINGW32)
        closesocket(this->myServerEx->getConnectfd());
#else
        close(this->myServerEx->getConnectfd());
#endif
        ret = baseServer::E_NOK;
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
          ret = handler->GetState();
        }
        else
        {
          this->recv_OK = FALSE;
        }
      }
    }
  }
#if 0
  memset(msg_head, 0, RECHEAD_SIZE);
  len = recv(this->myServerEx->getConnectfd(), (char *)msg_head, RECHEAD_SIZE, MSG_WAITALL);
  //cout << "recv len=" << len << endl;
  if ((len == SOCKET_ERROR) || (len == 0))
  {
    this->recv_OK = FALSE;
    std::cout << "exit1" << std::endl;
#if defined(MINGW32)
    closesocket(this->myServerEx->getConnectfd());
#else
    close(this->myServerEx->getConnectfd());
#endif
    ret = baseServer::E_NOK;
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
      ret = handler->GetState();
    }
    else
    {
      this->recv_OK = FALSE;
    }
  }
#endif
  return (ret);
}

int revHeadState::CurrentState(recvhandler *handler)
{
  return (revHead(handler));
}
revCmdState::revCmdState(ServerEx *serv)
{
  this->myServerEx = serv;
}
int revCmdState::revCmd(recvhandler *handler)
{
  uchar msg_cmd[RECCMD_SIZE];
  int len = 0;
  int ret = baseServer::E_OK;
  this->myServerEx->select_zero();
  this->myServerEx->select_set();
  ret = this->myServerEx->myselect();
  if (ret == -1)
  {
    debug_Log("cmd recv error");
    return (baseServer::E_NOK);
  }
  else if (ret == 0)
  {

    debug_Log("no cmd recv");
    //timeout error
    this->myServerEx->socketDisconnect();
    //close(this->myServerEx->getConnectfd());
    return(baseServer::E_NOK);
    //replay
    //handler->SetState(new revCmdState(handler->_myServ));
    //ret = handler->GetState();
  }
  else
  {
    memset(msg_cmd, 0, RECCMD_SIZE);
    len = recv(this->myServerEx->getConnectfd(), (char *)msg_cmd, RECCMD_SIZE, MSG_WAITALL);
    if ((len == SOCKET_ERROR) || (len == 0))
    {
      this->recv_OK = FALSE;
      std::cout << "exit2" << std::endl;
#if defined(MINGW32)
      closesocket(this->myServerEx->getConnectfd());
#else
      close(this->myServerEx->getConnectfd());
#endif
      ret = baseServer::E_NOK;
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
        ret = handler->GetState();
      }
      else
      {
        this->recv_OK = FALSE;
      }
    }
  }
#if 0
  memset(msg_cmd, 0, RECCMD_SIZE);
  len = recv(this->myServerEx->getConnectfd(), (char *)msg_cmd, RECCMD_SIZE, MSG_WAITALL);
  if ((len == SOCKET_ERROR) || (len == 0))
  {
    this->recv_OK = FALSE;
    std::cout << "exit2" << std::endl;
#if defined(MINGW32)
    closesocket(this->myServerEx->getConnectfd());
#else
    close(this->myServerEx->getConnectfd());
#endif
    ret = baseServer::E_NOK;
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
      ret = handler->GetState();
    }
    else
    {
      this->recv_OK = FALSE;
    }
  }
#endif
  return (ret);
}

int revCmdState::CurrentState(recvhandler *handler)
{
  return (revCmd(handler));
}
revDataState::revDataState(ServerEx *serv)
{
  this->myServerEx = serv;
}
int revDataState::revData(recvhandler *handler)
{
  int ret = baseServer::E_OK;
  int size = 0;
  handler->_myServ->revOK = FALSE;
  //cout<<"server:revData length:"<<srecvState.Msg.length<<endl;
  int baseindex =0;
  int savelength=this->Msglength;
  //start shm
  //char * sharebuf=&mysharebuf[0];
  handler->_myServ->sem->sem_p();
  char *sharebuf=handler->_myServ->shm->atAddr();
  while (this->Msglength > 0)
  {
    this->myServerEx->select_zero();
    this->myServerEx->select_set();
    ret = this->myServerEx->myselect();
    if (ret == -1)
    {
      debug_Log("revData error");
      std::cout<<"errorNO is "<<errno<<std::endl;
      return (baseServer::E_NOK);
    }
    else if (ret == 0)
    {
      debug_Log("no data recv");
      //timeout error
      this->myServerEx->socketDisconnect();
      //close(this->myServerEx->getConnectfd());
      return(baseServer::E_NOK);
      //replay
      //handler->SetState(new revDataState(handler->_myServ));
      //ret = handler->GetState();
    }
    else
    {
      size = recv(this->myServerEx->getConnectfd(), (char *)&this->Msgbuffer[0], BUFFER_SIZE, 0);
      
      
      if (size <= 0)
      {
        std::cout << "exit3" << std::endl;
#if defined(MINGW32)
        closesocket(this->myServerEx->getConnectfd());
#else
        close(this->myServerEx->getConnectfd());
#endif
        break; //diconnection
        ret = baseServer::E_NOK;
      }
      #if 0
      for (int i = 0; i < size; i++)
      {
        //this->vec.push_back(this->Msgbuffer[i]);
        sharebuf[baseindex+i]=this->Msgbuffer[i];
      }
      #endif
      memcpy(&sharebuf[baseindex],Msgbuffer,size);
      this->Msglength = this->Msglength - size;
      baseindex=baseindex+size;
      //std::cout<<"baseindex"<<baseindex<<std::endl;
      //std::cout<<"size="<<size<<std::endl;
      //std::cout<<"length="<<this->Msglength<<std::endl;
    }
  }
  //stop shm
  handler->_myServ->shm->DelAddr(sharebuf);
  handler->_myServ->sem->sem_v();
  if (ret == baseServer::E_NOK)
  {
    return (ret); //break;
  }
  //std::cout<<"baseindex= "<<baseindex<<std::endl;
  handler->_myServ->page++;
  MYmsg::Msg servbuf ;
  servbuf.groupID=MYGROUP;
  servbuf.eventID=1;
  servbuf.buf[0]=handler->_myServ->page;
  servbuf.buf[1]=baseindex;
  servbuf.buf[2]=0;
  servbuf.buf[3]=0;
  //send the page number
  handler->_myServ->msg->IPCsendMsg(&servbuf);
  //cout<<"page number is "<<handler->_myServ->page<<endl;
  // handler->_myServ->Img = cv::imdecode(this->vec, CV_LOAD_IMAGE_COLOR);
  // this->vec.clear();
  // std::vector<uchar>(this->vec).swap(this->vec);
  // handler->_myServ->revOK = TRUE;
  return (ret);
}

int revDataState::CurrentState(recvhandler *handler)
{
  return (revData(handler));
}

int baseServer::socketCreate(int type, int selection, int ip, int port)
{
  int ret = E_OK;
  this->serverfd = socket(type, selection, 0);
  if (this->serverfd == -1)
  {
    ret = E_NOK;
    std::cout << "accept failed!" << std::endl;
    exit(0);
  }
  //if we don't close sokect connect,we can reuse the same port.
  int opt =1;
  int len = sizeof(opt);
  setsockopt(this->serverfd,SOL_SOCKET,SO_REUSEADDR,&opt,len);

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
    std::cout << "bind failed!" << std::endl;
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
    std::cout << "listen failed!" << std::endl;
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
    std::cout << errno << std::endl;
    std::cout << "accept failed!" << std::endl;
    exit(0);
  }
  return (ret);
}

int baseServer::socketDisconnect(void)
{
  int ret = E_OK;
  debug_Log("socketDisconnect");
#if defined(MINGW32)
  ret = closesocket(this->connectfd);
#else
  ret = close(this->connectfd);
#endif
  if (ret == -1)
  {
    std::cout << "closesocket failed!" << std::endl;
    exit(0);
  }
  return (ret);
}

int baseServer::socketCloseServer(void)
{
  int ret = E_OK;
  debug_Log("socketCloseServer");
#if defined(MINGW32)
  ret = closesocket(this->serverfd);
#else
  ret = close(this->serverfd);
#endif
  if (ret == -1)
  {
    std::cout << "socketCloseServer failed!" << std::endl;
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
  this->msg = new MYmsg(this);
  this->shm = new myshm(this);
  this->sem = new mysem(this);
  this->revOK = FALSE;
  this->beat = ctrl::typeMain::transData;
  this->once = 0;
  this->page = 0; /* page number */
  this->tv.tv_sec = 3;
  this->tv.tv_usec = 0;
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
  int ret = E_OK;
  recvhandler *handler = new recvhandler(new revHeadState(this), this);
  ret = handler->GetState();
  return (ret);
}
int ServerEx::socketSendBeatFrame(uchar *cmdFrame)
{
  int ret = E_OK;
  //debug_Log("send beat");
  ret = send(getConnectfd(), (char *)cmdFrame, 10, 0);
  if (ret <= 0)
  {

  error_Log("socketSendBeatFrame error");
#if defined(MINGW32)
    
    closesocket(getConnectfd());
#else
    //close(getConnectfd());
#endif
  }
  return (ret);
}
int ServerEx::socketSendCmdFrame(uchar *cmdFrame)
{
  int ret = E_OK;

  if (this->sendSubCmd == ctrl::typeSubMain::enable)
  {
    this->once = 0;
    cmdFrame[5] = 1;
    ret = send(getConnectfd(), (char *)cmdFrame, 10, 0);
    if (ret <= 0)
    {
      error_Log("socketSendCmdFrame error");
#if defined(MINGW32)
      closesocket(getConnectfd());
#else
      //close(getConnectfd());
#endif
      return (E_NOK);
    }
    ret = ReceiveDataFrame();
    if (ret <= 0)
    {
      debug_Log("rec error");
      return (E_NOK);
    }
  }
  else
  {
    if (once == 0) /* add once to reduce busload */
    {
      cmdFrame[5] = 0;
      ret = send(getConnectfd(), (char *)cmdFrame, 10, 0);
      if (ret <= 0)
      {
        //std::cout << "exit4.1" << std::endl;
        error_Log("connnect error");
#if defined(MINGW32)
        closesocket(getConnectfd());
#else
        close(getConnectfd());
#endif
        return (E_NOK);
      }
      once = 1;
    }
  }

  return (ret);
}
void ServerEx::select_clr()
{
  FD_CLR(this->getConnectfd(), &this->read_fds);
}
void ServerEx::select_zero()
{
  FD_ZERO(&this->read_fds);
}
void ServerEx::select_set()
{
  FD_SET(this->getConnectfd(), &this->read_fds);
}
int ServerEx::select_iset()
{
  return (FD_ISSET(this->getConnectfd(), &this->read_fds));
}
int ServerEx::myselect()
{
  this->tv.tv_sec=3;   //reset the timeout value
  this->tv.tv_usec=0;
  return (select(this->getConnectfd() + 1, &this->read_fds, NULL, NULL, &this->tv));
}
int ServerEx::socketDataHandler()
{
  int ret = E_OK;
  while (1)
  {
    if (sendCmd == ctrl::typeMain::beat)
    {
      this->_mylock->startLockCmd();
      sendCmd = ctrl::typeMain::transData;
      this->_mylock->stopLockCmd();

      cmdBuff[4] = ctrl::typeMain::beat;
      ret = socketSendBeatFrame(&this->cmdBuff[0]);
    }
    else
    { /* normal */
      cmdBuff[4] = ctrl::typeMain::transData;
      ret = socketSendCmdFrame(&this->cmdBuff[0]);
    }
    if (ret <= 0)
    {
      debug_Log("break");
      break;
    }
  }

  return (0);
}
