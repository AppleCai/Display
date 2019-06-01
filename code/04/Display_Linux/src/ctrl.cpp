#include "server.hpp"
#include "key.hpp"

void ctrl::checksubType()
{
    this->cmdSubType = this->_mykey->getTransCmd();
    switch (this->cmdSubType)
    {
    case (ctrl::typeSubMain::enable):
    {
        this->_myServerEx->sendTrans(1);
        break;
    }
    case (ctrl::typeSubMain::disable):
    {
        this->_myServerEx->sendTrans(0);
        break;
    }
    case (ctrl::typeSubMain::otherSubType):
    {
        /* reserved */
        break;
    }
    default:
        break;
    }
}


void ctrl::ctrllogicHMI()
{
    if(this->_mykey->getJumpInfo())
    {
        /*no display*/
        this->_myHmi->SetShowEn(FALSE);
    }
    else
    {
        this->_myHmi->SetShowEn(TRUE);
    }
}
ctrl::ctrl(display* disp)
{
    disp->_myctrl=this;
    this->_myServerEx=disp->_myServerEx;
    this->_mykey=disp->_mykey;
    this->_myHmi=disp->_myHMI;
    cmdType=1;
    cmdSubType=1;
}
void ctrl::ctrllogicTrans()
{
    /* control for transmit data */
    this->cmdType = this->_myServerEx->getBeat();
    switch (this->cmdType)
    {
    case (ctrl::typeMain::transData):
    {
        checksubType();
        break;
    }
    case (ctrl::typeMain::beat):
    {
        this->_myServerEx->sendBeatCmd(); /* set flag to send beat message */
        this->_myServerEx->resetBeat();
        break;
    }
    case (ctrl::typeMain::otherType):
    {
        /* reserved */
        break;
    }
    default:
        break;
    }
}

void ctrl::ctrllogic()
{
    while (1)
    {
        ctrllogicTrans();
        ctrllogicHMI();
        //no display
        //this->_myHmi->DisplayFrame(this->_myServerEx);
    }
}