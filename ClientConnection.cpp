#include "ClientConnection.h"

void ClientConnection::begin(ServerConnection * sc) {
	serverConnection = sc;

	Serial.print(F("Trying connection to SSID "));
	Serial.print(WiFi.SSID());
	Serial.print(F(" and password "));
	Serial.println(WiFi.psk());

	WiFi.begin(WiFi.SSID().c_str(), WiFi.psk().c_str());

	Serial.println("Began WiFi");
}

void ClientConnection::loop() {
	if (WiFi.status() != WL_CONNECTED) {
		// Right now, we're not connected
		if (status != STATUS_NOT_CONNECTED) {
			// But last loop, we were
			// State change
			Serial.print(F("Lost connection to WiFi "));
			Serial.println(WiFi.SSID());
			status = STATUS_NOT_CONNECTED;

			serverConnection->enableLocalAP();
		}
	} else {
		if (status != STATUS_CONNECTED) {
			// State change
			Serial.print(F("Successfully connected to WiFi "));
			Serial.println(WiFi.SSID());
			Serial.print(F("The IP address is "));
			Serial.println(WiFi.localIP());
			status = STATUS_CONNECTED;

			serverConnection->disableLocalAP();
		}
	}
}