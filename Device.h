#ifndef DEVICE__H
#define DEVICE_H

#include <stdint.h>
#include <Arduino.h>

#define MAX_NAME_LENGTH 40
#define NUM_DEVICES 4

using namespace std;

class Device {
	public:
		Device(uint8_t id_[8], char name_[MAX_NAME_LENGTH], uint8_t pin_): pin(pin_) {
			for (uint8_t i = 0; i < 8; i++) {
				id[i] = id_[i];
			}
			for (uint8_t i = 0; i < MAX_NAME_LENGTH; i++) {
				name[i] = name_[i];
			}
		};

		static void setupDevices(uint8_t * macAddress, Device * * devices);

		/**
		 * ID of outlet.
		 */
		uint8_t id[8];

		/**
		 * Name of outlet.
		 */
		char name[MAX_NAME_LENGTH];

		/**
		 * Hardware pin.
		 */
		uint8_t pin;
};

#endif