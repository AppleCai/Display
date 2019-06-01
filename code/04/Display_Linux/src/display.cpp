#include "display.hpp"

display::display()
{
    _myServerEx = new ServerEx(this);
    _mykey = new key(this);
    _myHMI = new HMI(this);
    /* notes:shall create object first,otherwise the ctrl init works wrong */
    _myctrl = new ctrl(this);
}

void display::run(display *disp)
{
    int ret = 0;

    disp->_myServerEx->socketCreate(AF_INET, SOCKET_TYPE, INADDR_ANY, PORT_ID);
    disp->_myServerEx->socketBind();
    disp->_myServerEx->socketListen(2);
    if(disp->_myServerEx->shm->CreateShm())
    {
        exit(0);
    }
    disp->_myServerEx->sem->CreateSem(1, 33);
    disp->_myServerEx->sem->sem_get();
    disp->_myServerEx->sem->sem_init(1);
    disp->_myServerEx->msg->CreateMsg();
    std::thread taskKey(&key::KeyDetect, std::ref(disp->_mykey));
    std::thread taskCtrlandDisplay(&ctrl::ctrllogic, std::ref(disp->_myctrl));
    std::thread taskBeat(&ServerEx::BeatDetect, std::ref(disp->_myServerEx));
    pid_t id = fork();
    std::cout << "pid=" << id << std::endl;

    if (id < 0)
    {
        std::cout << "fork error" << std::endl;
        //return -1;
    }
    else if (id == 0) //child read
    {
        std::vector<uchar> imgvec;
        MYmsg::Msg recvbuf,cmdbuf;
        cmdbuf.buf[0]=0;  //init value,shall show pic
        while (1)
        {
            
            disp->_myServerEx->msg->IPCrecvMsg(&recvbuf,MYGROUP,0);
            //std::cout << "child:received page number and length " << recvbuf.buf[0] <<" "<<recvbuf.buf[1]<< std::endl;
            disp->_myServerEx->sem->sem_p();
            char *buf = disp->_myServerEx->shm->atAddr();
            for (int i = 0; i < recvbuf.buf[1] ; i++)
            {
                imgvec.push_back(buf[i]);
            }
            disp->_myServerEx->shm->DelAddr(buf);
            disp->_myServerEx->sem->sem_v();
            cv::Mat Img = cv::imdecode(imgvec, CV_LOAD_IMAGE_COLOR);
            imgvec.clear();
            std::vector<uchar>(imgvec).swap(imgvec);
            //cv::imshow("pic", Img);
            //cv::waitKey(1);
            cmdbuf.buf[1]=0; // clear the save bit each cycle
            disp->_mykey->msg->IPCrecvMsg(&cmdbuf,KEYGROUP,IPC_NOWAIT);
            if(0==cmdbuf.buf[0])
            {
                disp->_myHMI->DisplayFrame(Img,recvbuf.buf[0],cmdbuf.buf[1]);
            }
        }
    }
    else
    {
        while (1)
        {
            ret = disp->_myServerEx->socketAccept();
            std::cout << "h";
            if (ret == baseServer::E_OK)
            {
                std::cout << "connect sucess" << std::endl;
                disp->_myServerEx->socketDataHandler();
            }
        }
    }
    disp->_myServerEx->msg->delMsg();
    taskKey.join();
    taskCtrlandDisplay.join();
    taskBeat.join();
}
