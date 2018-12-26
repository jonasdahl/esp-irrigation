#ifndef SERVER_CONNECTION__H
#define SERVER_CONNECTION__H

#include <ESP8266WiFi.h>

#define STATUS_NEVER_CONNECTED 0
#define CONNECTION_BUFFER_SIZE 50

class ServerConnection {
	public:
		/**
		 * Inits the connection object. Must be called before any other method of the class.
		 * 
		 * @param ssid     the SSID of any temporary network
		 * @param password the password of temporary network
		 * @param ip       the device IP when used temporary
		 * @param netmask  the netmask of temporary network
		 */
		void begin(char * ssid, char * password, IPAddress * ip, IPAddress * netmask);

		/**
		 * Should be called repeatedly to execute small connection related tasks.
		 */
		void loop();

		/**
		 * Sets this device into AP mode for configuration devices to access.
		 */
		void enableLocalAP();

		/**
		 * Disables the local access point function.
		 */
		void disableLocalAP();

	private:
		/**
		 * Parses the remainder of the buffer.
		 */
		void parseBuffer();

		/**
		 * Sets the buffer values to 0.
		 */
		void resetBuffer();

		/**
		 * Returns the rest of the string from the given index.
		 */
		void parseString(uint8_t, char *);

		/**
		 * The SSID of the temporary access point.
		 */
		char * temporarySsid;

		/**
		 * The password of the temporary access point.
		 */
		char * temporaryPassword;

		/**
		 * The IP of the device when acting as AP.
		 */
		IPAddress * temporaryIp;

		/**
		 * The netmask of the network when acting as temporary AP.
		 */
		IPAddress * temporaryNetmask;

		/**
		 * The internal status of connection.
		 */
		uint8_t status = STATUS_NEVER_CONNECTED;

		/**
		 * The wifi server.
		 */
		WiFiServer * server;

		/**
		 * The client of the temporary AP.
		 */
		WiFiClient client;

		/**
		 * A buffer for storing received messages.
		 */
		char buffer[CONNECTION_BUFFER_SIZE];

		/**
		 * Index where the buffer is at the time.
		 */
		uint8_t bufferIndex = 0;
};

#endif