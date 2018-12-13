#ifndef SERVER
#define SERVER

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

using namespace std;

class Server {
public:
	Server();
	~Server();

	void init();
	void update();
	void shutDown();

private:
	WSADATA wsData;
	WORD ver;
	int wsOk;
	SOCKET listening;
	sockaddr_in hint;
	fd_set master;
	fd_set copy;
	int socketCount;
	SOCKET sock;
	SOCKET client;
	SOCKET outSock;
	bool running;

};


#endif // !SERVER

