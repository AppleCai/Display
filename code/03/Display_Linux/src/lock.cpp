#include "lock.hpp"
using namespace std; 
mutex mtx,mtxCmd;
condition_variable event;

bool check()
{
	//return (k.getTransCmd());
	return (1);/*reseved */
}

void mylock::startLockCmd()
{
	std::unique_lock<std::mutex> lck(mtxCmd);
}

void mylock::stopLockCmd()
{
	mtxCmd.unlock();
}

void mylock::startLock()
{
	std::unique_lock<std::mutex> lck(mtx);
}

void mylock::stopLock()
{
	mtx.unlock();
}

void mylock::eventTrigger()
{
	event.notify_one();
}

void mylock::waitEvent()
{
#if (MYDEBUG == TRUE)
	std::cout << "transmit stop" << std::endl;
#endif
	std::unique_lock<std::mutex> lck(mtx);
	event.wait(lck, check);
}
