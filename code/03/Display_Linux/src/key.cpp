#include "key.hpp"
using namespace std;

key::key(display* disp)
{
	disp->_mykey=this;
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
#if (MYDEBUG == TRUE)
			cout << "jump change to " << this->jump << endl;
#endif
		}
		else
		{
		}
	}

	return 0;
}