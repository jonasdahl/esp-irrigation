#include "ServerConnection.h"
#include <ESP8266WiFi.h>

void ServerConnection::begin(char * ssid, char * password, IPAddress * ip, IPAddress * netmask) {
	temporarySsid = ssid;
	temporaryPassword = password;
	temporaryIp = ip;
	temporaryNetmask = netmask;

	Serial.println("Began AP");
}

void ServerConnection::loop() {
	// Check if a config client has connected and if so, check if there is data
	return;


	if (!client.connected()) {
		client = server->available();
	} else {
		if (client.available() > 0) {
			buffer[bufferIndex] = client.read();
			++bufferIndex;
			if ((int) buffer[bufferIndex - 1] == 10 || bufferIndex + 1 >= CONNECTION_BUFFER_SIZE) {
				buffer[bufferIndex + 1] = '\0';
				bufferIndex = 0;
			}
		}
	}

	if (bufferIndex == 0) {
		parseBuffer();
	}
}

void ServerConnection::parseBuffer() {
	if (strlen(buffer) <= 0) {
		return;
	}

	switch (buffer[0]) {
		case 's': {
			// Someone sent a password, probably
			if (buffer[1] != ':') return;
			char realSsid[CONNECTION_BUFFER_SIZE - 2];
			parseString((uint8_t)2, realSsid);
			Serial.print("Got SSID ");
			Serial.println(realSsid);
			break;
		}
		case 'p': {
			// Someone sent a password, probably
			if (buffer[1] != ':') return;
			char realPassword[CONNECTION_BUFFER_SIZE - 2];
			parseString((uint8_t)2, realPassword);
			Serial.print("Got password ");
			Serial.println(realPassword);
			break;
		}
	}

	resetBuffer();
}

void ServerConnection::parseString(uint8_t startIndex, char * result) {
	for (int x = startIndex; x < CONNECTION_BUFFER_SIZE && buffer[x + 1] != '\0'; ++x) {
		if (buffer[x] != '\n') {
			result[x] = buffer[x + 2];
		}
	}
}

void ServerConnection::resetBuffer() {
	for (int i = 0; i < CONNECTION_BUFFER_SIZE; i++) {
		buffer[i] = '\0';
	}
}

void ServerConnection::enableLocalAP() {
	Serial.println("Enabling local AP");

	// Enter AP mode
	WiFi.mode(WIFI_AP_STA);

	// Configure the AP
	WiFi.softAPConfig(*temporaryIp, *temporaryIp, *temporaryNetmask);

    // Start it
	WiFi.softAP(temporarySsid, temporaryPassword);

    // Useful for debugging purposes
	Serial.print(F("Local AP started with IP: "));
	Serial.println(WiFi.softAPIP());
}

void ServerConnection::disableLocalAP() {
	Serial.println("Disabling local AP");

	WiFi.softAPdisconnect();
    WiFi.disconnect();
    
	WiFi.mode(WIFI_STA);

    Serial.println(F("Local AP disabled"));
}
