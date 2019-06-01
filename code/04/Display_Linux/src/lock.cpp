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

int myshm::CreateShm()
{
  key_t _key=ftok(PATHNAME,PROJ_ID);
  if(_key<0)
  {
    std::cout<<"Shm ftok error"<<std::endl;
    return -1;
  }
  //std::cout<<"key="<<_key<<std::endl;
  this->shmid=shmget(_key,MYSIZE,IPC_CREAT|0666);
  std::cout<<"shmget id="<<this->shmid<<std::endl;
  if(this->shmid<0)
  {
    std::cout<<"shmget error"<<std::endl;
    std::cout<<"shmget errno"<<errno<<std::endl;
    return -1;
  }
  return 0;  
}

char* myshm::atAddr()
{
  return (char *)shmat(this->shmid,NULL,0);
}

int myshm::DelAddr(char* shmaddr)
{
  return shmdt(shmaddr);
}

int myshm::DestoryShm()
{
  return shmctl(this->shmid,IPC_RMID,NULL);
}

key_t mysem::CreateSem(int nums,int keyid)
{
  key_t keySem=ftok(PATHNAME,keyid);
  if(keySem<0)
  {
    std::cout<<"Sem ftok error"<<std::endl;
    std::cout<<"errorno="<<errno<<std::endl;
    return -1;
  }
  std::cout<<"keySem="<<keySem<<std::endl;

  this->semkey = keySem;
}

//��ʼ���ź���
void mysem::sem_init(int val)
{
  int ret;
  union semun semun;
  semun.val = val;
  ret = semctl(this->semid, 0, SETVAL, semun);
  if (ret < 0)
  {
    perror("semctl error.");
    std::cout<<"errorno="<<errno<<std::endl;
    exit(1);
  }
}
//��ȡ�ź�����һ���ź�����һ�����е�id
int mysem::sem_get()
{
  int _semid = semget(this->semkey, 1, IPC_CREAT);
  std::cout<<"semid="<<_semid<<std::endl;
  if (_semid < 0)
  {
    perror("semget error.");
    exit(1);
  }
  this->semid=_semid;
}
//�ź���P���������ź�������0���1����0�����
void mysem::sem_p()  //value for op:p=-1,v=1
{
  int ret;
  struct sembuf sembuf;
  sembuf.sem_num = 0;
  sembuf.sem_op = -1;   
  sembuf.sem_flg = 0;
  ret = semop(this->semid, &sembuf, 1);
  if (ret < 0)
  {
    perror("semop error");
    exit(1);
  }
} 

void mysem::sem_v()  //value for op:p=-1,v=1
{
  int ret;
  struct sembuf sembuf;
  sembuf.sem_num = 0;
  sembuf.sem_op = 1;   
  sembuf.sem_flg = 0;
  ret = semop(this->semid, &sembuf, 1);
  if (ret < 0)
  {
    perror("semop error");
    exit(1);
  }
} 
mysem::mysem(ServerEx *serv)
{
  serv->sem=this;
}

myshm::myshm(ServerEx *serv)
{
  serv->shm=this;
}

MYmsg::MYmsg(ServerEx *serv)
{
  serv->msg=this;
}

int MYmsg::CreateMsg()
{
  key_t _key=ftok(PATHNAME,PROJ_IDMsg);
  if(_key<0)
  {
    std::cout<<"MYmsg ftok error"<<std::endl;
    return -1;
  }
  std::cout<<"key="<<_key<<std::endl;
  this->msgid=msgget(_key,IPC_CREAT|0666);
  if(this->msgid<0)
  {
    std::cout<<"msgget error"<<std::endl;
    return -1;
  }  
}

int MYmsg::IPCsendMsg(MYmsg::Msg *buf)
{
  int ret =msgsnd(this->msgid,buf,sizeof(Msg)-sizeof(int),0);
  //std::cout<<"send msgid="<<this->msgid<<std::endl;
  if(-1==ret)
  {
    std::cout<<"msgsnd error"<<std::endl;
  }
}

int MYmsg::IPCrecvMsg(Msg * buf,int type,int wait)
{
  int ret =msgrcv(this->msgid,buf,sizeof(Msg)-sizeof(int),type,wait);
  //std::cout<<"recv msgid="<<this->msgid<<std::endl;
  if((-1==ret)&&(errno!=ENOMSG))
  {
    std::cout<<"msgrecv error"<<std::endl;
  }
}

int MYmsg::delMsg()
{
  return msgctl(this->msgid,IPC_RMID,NULL);
}
