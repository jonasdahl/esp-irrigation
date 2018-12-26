#ifndef CLIENT_CONNECTION__H
#define CLIENT_CONNECTION__H

#include <ESP8266WiFi.h>
#include "ServerConnection.h"

#define STATUS_NOT_CONNECTED 1
#define STATUS_CONNECTED 2

class ClientConnection {
	public:
		void begin(ServerConnection * sc);
		void loop();
	private:
		uint8_t status = STATUS_NOT_CONNECTED;
		ServerConnection * serverConnection;
};

#endif