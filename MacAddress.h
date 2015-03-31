#ifndef MAC_ADDRESS_h
#define MAC_ADDRESS_h

#include <Arduino.h>

class MacAddress {
public:
	static String get();
private:
	static const unsigned int BUFFER_LENGTH = 6;
	static void read(uint8_t word, uint8_t *buffer, uint8_t offset);
};

#endif