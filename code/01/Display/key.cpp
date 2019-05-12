#include "key.hpp"
#include "server.hpp"
#include "windows.h"
using namespace cv;
keysearch k;
std::mutex mtx;
std::condition_variable event;
bool check()
{
	return (k.getTransCmd());
}

void myLock::startLock()
{
	std::unique_lock<std::mutex> lck(mtx);
}

void myLock::stopLock()
{
	mtx.unlock();
}

void myLock::eventTrigger()
{
	event.notify_one();
}

void myLock::waitEvent()
{
#if (MYDEBUG == TRUE)
	std::cout << "transmit stop" << std::endl;
#endif
	std::unique_lock<std::mutex> lck(mtx);
	event.wait(lck, check);
}

keysearch::keysearch()
{
	this->jump = 0;
	this->status = TRUE;
}
bool keysearch::getJumpInfo(void)
{
	return (this->jump);
}
bool keysearch::getTransCmd(void)
{
	return (this->status);
}

int keysearch::KeyDetect(void)
{
	while (1)
	{
		char key = getchar();
		if (key == 's')
		{
			this->keylock->startLock();
			this->status ^= 1;
#if (MYDEBUG == TRUE)
			std::cout << "transmit stop" << this->status << std::endl;
#endif
			this->keylock->eventTrigger();
		}
		else if (key == 'j')
		{
			this->jump ^= 1;
#if (MYDEBUG == TRUE)
			std::cout << "jump change to " << this->jump << std::endl;
#endif
		}
		else
		{
		}
	}

	return 0;
}
