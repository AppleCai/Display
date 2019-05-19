#ifndef CTRL_HPP
#define CTRL_HPP
#include "head.hpp"
class key;
class ServerEx;
class HMI;
class display;
class ctrl
{
public:
    enum typeMain{transData=1,beat=2,otherType=3};
    enum typeSubMain{disable=0,enable=1,otherSubType=2};
    //typedef std::shared_ptr<ctrl> Ptr;
    ctrl(display* disp);
    ~ctrl(){};
    void ctrllogic();
    void ctrllogicTrans();
    void ctrllogicHMI();
    void checksubType();
    int cmdType,cmdSubType;
private:
    key* _mykey;
    ServerEx* _myServerEx;
    HMI* _myHmi;
};
#endif