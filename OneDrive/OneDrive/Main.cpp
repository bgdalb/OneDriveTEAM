#include <iostream>
#include "FolderSync.h"
#include "UserDatabase.h"
#include "Connector.h"
#include <ws2tcpip.h>
#include <sstream>
#include <vector>
#include <string>
#pragma comment(lib, "Ws2_32.lib")	//  links to Ws2_32.lib

int main()
{
	Connector Connection(54000);
	Connection.setDBPath("UserDatabase.txt");
	Connection.run();
}