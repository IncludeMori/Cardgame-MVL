#include "connectPVP.hpp"


#include "SDLNet_init.hpp"
#include "connectionData.hpp"
#include "HostSocket.hpp"
#include "ClientSocket.hpp"
#include "Message.hpp"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
connectPVP::connectPVP()
{
	// Network status indicator

		bool Connected;

	// Network objects

	CClientSocket* tcpclient;

	CIpAddress* remoteip;

	CNetMessageApp msg;

	Connected = false;

	tcpclient = NULL;

	remoteip = NULL;

	// Creating Ip and Socket objects

		tcpclient = new CClientSocket();


	remoteip = new CIpAddress("192.168.2.105", 4444);

	std::string ID = "GUTENTAGMEINHERR";
	msg.LoadByte('x');

	tcpclient->Send(msg);
	cout << SDLNet_GetError() << endl;

	while (true)
	{
		if (!Connected) {

			if (tcpclient->Connect(*remoteip)) {
				cout << "connected" << endl;
				if (tcpclient->Ok()) {

					Connected = true;

				}
				else
					cout << SDLNet_GetError() << endl;

			}
			else
				cout << "connection failed" << endl;

		}
		else {
			charbuf s = "huan";
			msg.LoadBytes(s,255);
			msg.LoadByte('x');
			tcpclient->Send(msg);
			//if connected, checks the socket for messages ready to be read

			if (tcpclient->Ready()) {

				// if there is a message, try to receive it. In case of disconnection, the TCP protocol sends
		
				// a message with no bytes

				if (tcpclient->Receive(msg)) {

					//if there is a valid message, we can set the grid and player status

				}

				else {
					cout << "dc" << endl;
					Connected = false;

				}

			}

		}

	}


}