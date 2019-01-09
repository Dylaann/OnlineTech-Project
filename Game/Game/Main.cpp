#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2test.lib")
#pragma comment(lib, "SDL2_image.lib")

#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {

	string ipAddress = "149.153.106.145";			// IP Address of the server
	int port = 8080;						// Listening port # on the server

											// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return 0;
	}


	Game game;
	game.run();

	return 0;
}