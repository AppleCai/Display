#ifndef HMI_HPP
#define HMI_HPP
#include "head.hpp"

class HMI
{
public:
    //typedef std::shared_ptr<HMI> Ptr;
    HMI(display* disp);
    ~HMI(){};
    void DisplayFrame(ServerEx* serv);
    void ROIhandler(ServerEx *serv);
    void SetShowEn(bool cmd);
private:
   bool _showEn; 
};

#endif