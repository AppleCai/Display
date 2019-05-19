#include "display.hpp"

display::display()
{
    _myServerEx=new ServerEx(this);
    _mykey=new key(this);  
    _myHMI=new HMI(this); 
    /* notes:shall create object first,otherwise the ctrl init works wrong */
    _myctrl=new ctrl(this);
}

void display::run(display* disp)
{
    int ret = 0;
    if (disp->_myServerEx->socketCreate(AF_INET, SOCKET_TYPE, INADDR_ANY, PORT_ID))
    {
        error_Log("error:socketCreate");
        exit(0);
    }
    if (disp->_myServerEx->socketBind())
    {
        error_Log("error:socketBind");
        exit(0);
    }
    if (disp->_myServerEx->socketListen(2))
    {
        error_Log("error:socketListen");
        exit(0);
    }
    std::thread taskKey(&key::KeyDetect, std::ref(disp->_mykey));
    std::thread taskCtrlandDisplay(&ctrl::ctrllogic, std::ref(disp->_myctrl));
    std::thread taskBeat(&ServerEx::BeatDetect, std::ref(disp->_myServerEx));
    while (1)
    {
        ret = disp->_myServerEx->socketAccept();
        if (ret == 0)
        {
            std::cout<<"connect sucess"<<std::endl;
            disp->_myServerEx->socketDataHandler();
        }
    }
    taskKey.join();
    taskCtrlandDisplay.join();
    taskBeat.join();
}