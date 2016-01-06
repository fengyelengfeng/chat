/*tcpclithr.cpp*/

#include <stdio.h>
#include <vector.h>
#include "pthread.h"
#include "MySocket.h"
#include "MyThread.h"
#include "TcpCliThr.h"

TcpCliThr::TcpCliThr()
{
	ThrSet = new vector<MyThread*>();
}

TcpCliThr::TcpCliThr(int port,char *server):MySocket(AF_INET,SOCK_STREAM,0,port,server)
{
	ThrSet = new vector<MyThread*>();
}

TcpCliThr::~TcpCliThr()
{
	/*wait until all threads exits */
	WaitAllThr();
	/*free all memory of threads */
	vector<MyThread*>::iterator it =ThrSet->begin();
	while (it!=ThrSet->end())
	{
		MyThread* thr=(MyThread*)(*it);
		delete thr;
		it++;
	}
	delete ThrSet;
}

int TcpCliThr::ConnectServ()
{
	if(Connect()==-1) return -1;
	/*Create new thread */
	MyThread *Rthread,*Wthread;
	if(CreateThr(&Rthread,&Wthread)==-1) return -1;
	AddThread(Rthread);
	AddThread(Wthread);
	if(Rthread->Start()) return -1;
	if(Wthread->Start()) return -1;
	return 0;
}

int TcpCliThr::CreateThr(MyThread** Rthread,MyThread** Wthread)
{
	printf("Accept Conn\n");
	*Rthread=new Receiver(Mysocket,this);
	*Wthread=new Sender(Mysocket,this);
	return 0;
}

void TcpCliThr::DealRecv(MyThread* thread)
{
	printf("Receiver is running!\n");
}

void TcpCliThr::DealSend(MyThread* thread)
{
	printf("Sender is running!\n");

}

void TcpCliThr::AddThread(MyThread* thread)
{
	if(thread==NULL) return ;
	ThrSet->push_back(thread);
}

void TcpCliThr::DelThread(MyThread* thread)
{
	vector<MyThread*>::iterator it= ThrSet->begin();
	while(it !=ThrSet->end())
	{
		if(((MyThread*)*it)==thread)
		{
			ThrSet->erase(it);
			break;
		}
		it++;
	}
}

int TcpCliThr::WaitAllThr()
{
	vector<MyThread*>::iterator it=ThrSet->begin();
	while(it!=ThrSet->end())
	{
		MyThread* thr=(MyThread*)(*it);
		pthread_join(thr->getId(),NULL);
		it++;
	}
	return 0;
}
