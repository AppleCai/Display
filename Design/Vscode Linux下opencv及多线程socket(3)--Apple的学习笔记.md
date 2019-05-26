Vscode Linux下opencv及多线程socket(3)--Apple的学习笔记
继承我的上一篇文章[Vscode mingw下opencv及多线程socket(2)--Apple的学习笔记](https://www.jianshu.com/p/80f18bffae0a)中待完成任务。
##一，本周做了变更（版本变更为0.3）

	1. HMI图片显示添加ROI区域显示张数及叠加特质logo。
	2. Server端切换到linux系统上。
	3. recv存阻塞修改设计为select IO复用的异步形式，实现了断线也能重连的功能。
	4. 对client测试code的重连函数中connect函数也使用非阻塞，加快重连速度。

工程共享路径(在code/03文件夹中): https://github.com/AppleCai/Display

##二，后续更新版本说明：
之前的2.4/2.5算完成了，后续需要完成

	2.6 重构HMI，分离为一个进程。
	2.7	添加对图片的监视作用，添加弹窗报警及logDTC记录。（目的是使用进程间通信和共享内存）
	2.8	添加守护进程。
	2.9	进行性能测试，进行优化。

##三，图片叠加设计说明
	关于添加log及页数的方法：
	将页数转为单个的字符串，自己制作0~9及logo的图片。将个十百千数字的位置及logo的位置固定后，进行opencv的ROI区域叠加即可。在原有函数中添加ROIhandler处理函数。

```cpp
	void HMI::ROIhandler(ServerEx *serv)
	{
	    /* Add logo ROI */
	    cv::Mat mylogo = cv::imread("./pic/logo.png");
	    cv::Mat imgROIlogo = serv->Img(cv::Rect(0, 0, mylogo.cols, mylogo.rows));
	    mylogo.copyTo(imgROIlogo, mylogo);
	
	    std::string suffix = ".png";
	    /* int to string */
	    std::string res = std::to_string(serv->page);
	    /* stuff zero on the right*/
	    while (res.size() < 4)
	    {
	      res = "0" + res;
	    }
	    /* setting number ROI get each item in string */
	    cv::Mat numthousand = cv::imread("./pic/" + res.substr(0, 1) + suffix);
	    cv::Mat imgROInumthousand = serv->Img(cv::Rect(mylogo.cols + 10, 0, numthousand.cols, numthousand.rows));
	    numthousand.copyTo(imgROInumthousand, numthousand);
	
	    cv::Mat numhundred = cv::imread("./pic/" + res.substr(1, 1) + suffix);
	    cv::Mat imgROInumhundred = serv->Img(cv::Rect(mylogo.cols + 30, 0, numhundred.cols, numhundred.rows));
	    numhundred.copyTo(imgROInumhundred, numhundred);
	
	    cv::Mat numtens = cv::imread("./pic/" + res.substr(2, 1) + suffix);
	    cv::Mat imgROInumtens = serv->Img(cv::Rect(mylogo.cols + 50, 0, numtens.cols, numtens.rows));
	    numtens.copyTo(imgROInumtens, numtens);
	
	    cv::Mat numunits = cv::imread("./pic/" + res.substr(3, 1) + suffix);
	    cv::Mat imgROInumunits = serv->Img(cv::Rect(mylogo.cols + 70, 0, numunits.cols, numunits.rows));
	    numunits.copyTo(imgROInumunits, numunits);
	}
	
	void HMI::DisplayFrame(ServerEx *serv)
	{
	  if ((this->_showEn == TRUE) && (serv->revOK == TRUE))
	  {
	    ROIhandler(serv);
	    /* show picture */
	    cv::imshow("pic", serv->Img);
	    cv::waitKey(1);
	  }
	}

```
##四，关于select模型的设计说明
	一开始调试的时候，select过一段时间后就会一直返回0。明明已经设置了timeout时间为3s，这是为什么。通过wireshark监控没有发现超时，最后才知道每次select调用的时候timeout需要重新初始化为3s。
	经过修改后，除非断线，否则不会返回0。因为一帧图片数据在1s内即可传输完毕。select函数的设计框架如下。
```cpp
	  this->myServerEx->select_zero();
	  this->myServerEx->select_set();
	  //重新select需要重新设置timeout值
	  ret = this->myServerEx->myselect();
	  if (ret == -1)
	  {
	      //出错处理
	  }
	  else if (ret == 0)
	  {
	      //超时处理
	  }
	  else
	  {
		  if (this->myServerEx->select_iset())
		  {
		      //正常执行
		  }
	  }
```

```cpp
```

```cpp
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
```
##五，运行效果图
