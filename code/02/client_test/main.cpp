//client
#define MINGW32

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef MINGW32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <thread>
#define MAXLINE 1024
#define DEBUG FALSE

std::vector<std::string> rgb_files;
int sockfd, n;
struct sockaddr_in serveraddr;
int state;
int getPicture(void)
{
  using namespace std;
  string dataset_dir = "D:/ws/display/data";
  cout << "dataset: " << dataset_dir << endl;
  ifstream fin(dataset_dir + "/associate.txt");
  if (!fin)
  {
    cout << "please generate the associate file called associate.txt!" << endl;
    return 1;
  }

  vector<double> rgb_times;
  while (!fin.eof())
  {
    string rgb_time, rgb_file, temp1, temp2;
    fin >> rgb_time >> rgb_file >> temp1 >> temp2;
    //rgb_times.push_back ( atof ( rgb_time.c_str() ) );
    rgb_files.push_back(dataset_dir + "/" + rgb_file);
    if (fin.good() == false)
      break;
  }
  cout << "read total " << rgb_files.size() << " entries" << endl;
  return 0;
}
bool BeatConnect = TRUE;
void BeatDetect(void)
{
  while (1)
  {
    Sleep(5000);
    if (BeatConnect == FALSE)
    {
      std::cout << "disconntion" << std::endl;
#ifdef MINGW32
      //Winsows下关闭socket
      closesocket(sockfd);
      //WSACleanup();
#else
      close(sockfd);
#endif
      Sleep(1000); /*重连*/
      //建立socket
      state = 1;
      if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
      {
        printf("socket() fail\n");
        exit(0);
      }
      else
      {
        printf("socket() reconnect ok\n");
      }
      if (state = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
      {
        printf("connect() fail\n");
        exit(0);
      }
      else
      {
        printf("socket() reconnect ok2\n");
      }
    }
    BeatConnect = FALSE;
    std::cout << "BeatConnect=FALSE" << std::endl;
  }
}
int main(int argc, char **argv)
{

  char receline[MAXLINE + 1];

  std::thread t1(BeatDetect);
  t1.detach();
  //输入参数太少，退出
  if (argc != 2)
  {
    printf("Usage :%s IP_address\n", argv[0]);

    exit(0);
  }

#ifdef MINGW32
  //Winsows下启用socket
  WSADATA wsadata;
  if (WSAStartup(MAKEWORD(1, 1), &wsadata) == SOCKET_ERROR)
  {
    printf("WSAStartup() fail\n");
    exit(0);
  }
#endif

  //建立socket
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    printf("socket() fail\n");
    exit(0);
  }

  //设置协议及Port
  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(1024);

  //设置IP
  serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
  /* picture handler */
  getPicture();

  //连接
  if (state = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
  {
    printf("connect() fail\n");
    exit(0);
  }
  uchar cok[10] = {0x33};
  char cokstart[1] = {0};
  int size, i = 0;
  while (1)
  {
    std::cout << "g";
    while (i < rgb_files.size() && (state == 0))
    {
      size = 0;
      memset(cok, 0, 10);
      size = recv(sockfd, (char *)cok, 10, 0);
      if ((cok[0] == 0xA5) && (cok[1] == 0xA5) && (cok[2] = 0xA5) && (cok[3] = 0xff) && (cok[4] == 0x2))
      {
        std::cout << "get beat" << std::endl;
        BeatConnect = TRUE;
      }
      if ((cok[0] == 0xA5) && (cok[1] == 0xA5) && (cok[2] == 0xA5) && (cok[3] == 0xFF) &&
          (cok[4] == 0x1) && (cok[5] == 0x1))
      {

        //std::cout<<"rec success!"<<std::endl;
        cv::Mat image = cv::imread(rgb_files[i]);
        //TODO:需要添加判断读取文件是否成功
        //encode image and save to file
        std::vector<uchar> data_encode;
        cv::imencode(".png", image, data_encode);
        std::string str_encode(data_encode.begin(), data_encode.end());
        int length = data_encode.size();

        unsigned char msgLen[4];
        msgLen[0] = length >> 24;
        msgLen[1] = length >> 16;
        msgLen[2] = length >> 8;
        msgLen[3] = length;
        //std::cout << length << std::endl;
        //printf("datalen=%x\n",datalen);
#if 0
      char bufferCmd[10];
      bufferCmd[0]=0xA5;
      bufferCmd[1]=0xA5;
      bufferCmd[2]=0xA5;
      bufferCmd[3]=0xFF;     
      bufferCmd[4]=0x01;
      bufferCmd[5]=0x00;    
      bufferCmd[6]=msgLen[0]; 
      bufferCmd[7]=msgLen[1];    
      bufferCmd[8]=msgLen[2]; 
      bufferCmd[9]=msgLen[3]; 
      /* send cmd */
      send(sockfd, bufferCmd, 10, 0);

      char buffer[length];
      memcpy(buffer, &data_encode[0], length);
      // 向服务器发送buffer中的数据，此时buffer中存放的是客户端需要接收的文件的名字
#endif
        char buffer[length];
        buffer[0] = 0xA5;
        buffer[1] = 0xA5;
        buffer[2] = 0xA5;
        buffer[3] = 0xFF;
        buffer[4] = 0x01;
        buffer[5] = 0x00;
        buffer[6] = msgLen[0];
        buffer[7] = msgLen[1];
        buffer[8] = msgLen[2];
        buffer[9] = msgLen[3];
        memcpy(buffer + 10, &data_encode[0], length);
#ifdef MINGW32
        send(sockfd, buffer, length + 10, 0);
        //std::cout<<"send success!"<<std::endl;
        //recv(sockfd, cok, 1, 0);
#if (DEBUG == TRUE)
        std::cout << "next" << i << std::endl;
#endif
#else
        write(sockfd, buffer, strlen(buffer));
        read(sockfd, cok, 1, 0);
#endif
        i++;
        //std::cout<<"page ="<<i<<std::endl;
      }
    }
  }
  // #ifdef MINGW32
  //   //Winsows下关闭socket
  //   closesocket(sockfd);
  //   WSACleanup();
  // #else
  //   close(sockfd);
  // #endif

  //   exit(0);
}