#ifndef ORCHESTRA_MEMBER_CONFIG_h
#define ORCHESTRA_MEMBER_CONFIG_h

#include <Arduino.h>

struct orchestra_member_t {
	String macAddress;
	int midiChannel;
	bool klockMeister;
};

class OrchestraMemberConfig {
public:
	static const unsigned int MEMBER_COUNT = 11;
	static void getDefaultConfig(orchestra_member_t* list);
};

#endif