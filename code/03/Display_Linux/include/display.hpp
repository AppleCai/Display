#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "head.hpp"
class display
{
public:
    //typedef std::shared_ptr<display> Ptr;
    display();
    ~display(){};
    void run(display* disp);
    ServerEx* _myServerEx;
    ctrl* _myctrl;
    HMI* _myHMI;
    key* _mykey;
};

#endif