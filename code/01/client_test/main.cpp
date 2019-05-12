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
#define MAXLINE 1024
#define DEBUG FALSE

std::vector<std::string> rgb_files;

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

int main(int argc, char **argv)
{
  int sockfd, n;
  char receline[MAXLINE + 1];
  struct sockaddr_in serveraddr;

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
  if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
  {
    printf("connect() fail\n");
    exit(0);
  }
  char cok[1] = {0x55};
  char cokstart[1] = {0};

  for (int i = 0; i < rgb_files.size(); i++)
  {
    if (cok[0] == 0x55)
    {
      cok[0] = 0;
      cv::Mat image = cv::imread(rgb_files[i]);
      //TODO:需要添加判断读取文件是否成功
      //encode image and save to file
      std::vector<uchar> data_encode;
      cv::imencode(".png", image, data_encode);
      std::string str_encode(data_encode.begin(), data_encode.end());
      int length = data_encode.size();
      char buffer[length];
      memcpy(buffer, &data_encode[0], sizeof(buffer));

      unsigned char msgLen[4];
      msgLen[0] = length >> 24;
      msgLen[1] = length >> 16;
      msgLen[2] = length >> 8;
      msgLen[3] = length;
      //std::cout << length << std::endl;
      //printf("datalen=%x\n",datalen);

      // 向服务器发送buffer中的数据，此时buffer中存放的是客户端需要接收的文件的名字
#ifdef MINGW32
      send(sockfd, (char *)&msgLen[0], 4, 0);
      recv(sockfd, cokstart, 1, 0);
#else
      write(sockfd, msgLen, 4, 0);
      read(sockfd, cokstart, 1, 0);
#endif
      if (cokstart[0] == 0x33)
      {
        cokstart[0] = 0x0;
#ifdef MINGW32
        send(sockfd, buffer, length, 0);
        recv(sockfd, cok, 1, 0);
			#if (DEBUG == TRUE)
        std::cout<<"next"<<i<<std::endl;
	#endif
#else
        write(sockfd, buffer, strlen(buffer));
        read(sockfd, cok, 1, 0);
#endif
      }
    }
  }
#ifdef MINGW32
    //Winsows下关闭socket
    closesocket(sockfd);
    WSACleanup();
#else
    close(sockfd);
#endif

    exit(0);
  }