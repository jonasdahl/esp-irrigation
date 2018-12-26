#include "Device.h"

void Device::setupDevices(uint8_t * macAddress, Device * * devices) {
	for (int i = 0; i < NUM_DEVICES; ++i) {
		// ID is defaulted to mac address + 00:0X where x is 0..3
		uint8_t id[8] = {0};
		memcpy(id, macAddress, 6 * sizeof(uint8_t));
		id[6] = 0;
		id[7] = i;

		char name[MAX_NAME_LENGTH] = {0}; 
		strcpy(name, "Outlet ");
		name[7] = i + 0x31;
		name[8] = '\0';
		
		uint8_t pin = 0;
		switch (i) {
			case 0: pin = D1;
			case 1: pin = D2;
			case 2: pin = D3;
			case 3: pin = D4;
		}
		devices[i] = new Device(id, name, pin);

		pinMode(devices[i]->pin, OUTPUT);
		digitalWrite(devices[i]->pin, LOW);
	}
}