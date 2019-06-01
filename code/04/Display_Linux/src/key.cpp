#include "key.hpp"
using namespace std;

key::key(display* disp)
{
	disp->_mykey=this;
	this->msg=disp->_myServerEx->msg;
	this->jump = 0;
	this->status = TRUE;
}
bool key::getJumpInfo(void)
{
	return (this->jump);
}
bool key::getTransCmd(void)
{
	return (this->status);
}

int key::KeyDetect(void)
{

	while (1)
	{

		char key = getchar();
		if (key == 's')
		{
			this->status ^= 1;
#if (MYDEBUG == TRUE)
			cout << "transmit stop" << this->status << endl;
#endif
		}
		else if (key == 'j')
		{
			this->jump ^= 1;
			MYmsg::Msg keybuf ;
  			keybuf.groupID=KEYGROUP;
  			keybuf.eventID=1;
  			keybuf.buf[0]=this->jump;
  			keybuf.buf[1]=0;
  			keybuf.buf[2]=0;
  			keybuf.buf[3]=0;
  			//send the page number
  			this->msg->IPCsendMsg(&keybuf);
#if (MYDEBUG == TRUE)
			cout << "jump change to " << this->jump << endl;
#endif
		}
		else if (key == 'p')
		{
			MYmsg::Msg keybuf ;
  			keybuf.groupID=KEYGROUP;
  			keybuf.eventID=1;
  			keybuf.buf[0]=this->jump;
  			keybuf.buf[1]=TRUE;
  			keybuf.buf[2]=0;
  			keybuf.buf[3]=0;
  			//send the page number
  			this->msg->IPCsendMsg(&keybuf);			
		}
		else
		{
		}
	}

	return 0;
}