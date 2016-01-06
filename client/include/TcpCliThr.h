/*************************************
 *class name : TcpCliThr
 *Function : support Tcp client with multithread
 * ***************************************/

class TcpCliThr : public MySocket
{
	vector <MyThread*>* ThrSet;
	
	public:
	TcpCliThr();
	TcpCliThr(int port,char* server);
	virtual ~TcpCliThr();

	int ConnectServ();
	virtual void DealRecv(MyThread* thread);
	virtual void DealSend(MyThread* thread);
	protected:
	int CreateThr(MyThread** Rthread,MyThread** Wthread);
	void AddThread(MyThread* thread);
	void DelThread(MyThread* thread);
	int WaitAllThr();
	class Receiver : public MyThread
	{
		public:
			int socket;
			TcpCliThr* server;
			Receiver(int connsocket,TcpCliThr* serv)
			{
				socket=connsocket;
				server=serv;
			}
			void run(){server->DealRecv(this);}
	};
	class Sender : public MyThread
	{
		public:
			int socket;
			TcpCliThr* server;
			Sender(int connsocket,TcpCliThr* serv)
			{
				socket=connsocket;
				server = serv;
			}
			void run(){server->DealSend(this);}
	};
} ;
