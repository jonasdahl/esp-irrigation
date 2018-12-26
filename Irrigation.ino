#include <ESP8266WiFi.h>
#include "Device.h"
#include "ClientConnection.h"
#include "ServerConnection.h"

/**
 * Temporary AP settings
 */
char *apSSID = "DahlIrrigation_E34D";
char *apPassword = "password";
IPAddress apIP(192, 168, 1, 1);
IPAddress apNetmask(255, 255, 255, 0);
#define AP_PORT 8888

/**
 * Outlet settings
 */
Device * devices[4];

/**
 * General variables.
 */
uint8_t macAddress[6] = { 0 };
ClientConnection wifi;
ServerConnection ap;

/**
 * Run when powered on.
 */
void setup() {
    Serial.begin(115200);
    Serial.println(F("Starting up"));

    //WiFi.macAddress(macAddress);
    //Serial.print(F("This device has MAC address "));
    //Serial.println(macAddress);

    Serial.println("Beginning AP");
    ap.begin(apSSID, apPassword, &apIP, &apNetmask);
    Serial.println("Beginning Wifi");
    wifi.begin(&ap);
    Serial.println("Creating devices");
    Device::setupDevices(macAddress, devices);
    Serial.println("Done setup");
}

/**
 * Run repeatedly until power off.
 */
void loop() {
    ap.loop();
    wifi.loop();
}
