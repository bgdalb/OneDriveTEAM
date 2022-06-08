#include "mainwindow.h"
#include "loginscreen.h"
#include <QApplication>
#include <ws2tcpip.h>
#include <serverconnector.h>

int main(int argc, char* argv[])
{
	ServerConnector con;
	con.setIP("127.0.0.1");
	con.setPort(54000);
	con.Socketconnect();
	QApplication a(argc, argv);
	LoginScreen log;
	log.setConnection(con);
	log.show();
	return a.exec();
}
