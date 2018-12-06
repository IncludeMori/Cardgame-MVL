#include "initPVP.hpp"


/*
#include "SDLNet_init.hpp"
#include "connectionData.hpp"
#include "HostSocket.hpp"
#include "ClientSocket.hpp"
#include "Message.hpp"

#include <iostream>
#include <string>

using std::cout;
using std::endl;

initPVP::initPVP()
{
	//host
	CClientSocket* tcpclient;

	CHostSocket* tcplistener;

	CNetMessageApp msg;

	tcplistener = NULL;

	tcpclient = NULL;

	bool Connected = false;

	cout << "creating socket..." << endl;
	tcplistener = new CHostSocket(4444);
	cout << "socket-> done" << endl;

	if (!tcplistener->Ok())
		std::cout << "ERROR";

	//Creating client socket

	tcpclient = new CClientSocket();

	while (true)
	{
		if (!Connected) {

			if (tcplistener->Accept(*tcpclient)) {

				Connected = true;

			}
		}
		else {

			//if connected, checks the socket for messages ready to be read

			if (tcpclient->Ready()) {
				// if there is a message, try to receive it. In case of disconnection, the TCP protocol sends

				// a message with no bytes

				if (tcpclient->Receive(msg)) {

					//if there is a valid message, we can set the grid and player status
					std::cout << "revieved:" << msg.UnLoadByte() << endl;

				}
				else
				{
					cout << "dc server" << endl;
					Connected = false;
				}
			}
		}

		//delete tcplistener;

		//delete tcpclient;
	}

}

*/