#ifndef AUTOMATIC_ORCHESTRA_h
#define AUTOMATIC_ORCHESTRA_h

#include <Arduino.h>
#include "BodyseqSynth.h"
#include "MacAddress.h"
#include "OrchestraMemberConfig.h"

class AutomaticOrchestra {
public:
	AutomaticOrchestra();
	const String getMacAddress();
	const int getMidiChannel();
	const bool isKlockmeister();
	void handleSequencerTick();
	void handleNoteOn(byte channel, byte note, byte velocity);
	void handleNoteOff(byte channel, byte note, byte velocity);
	void handleControlChange(byte channel, byte control, byte value);
private:
	String mMacAddress;
	int mMidiChannel;
	bool mKlockmeister;
};

#endif