#ifndef AUTOMATIC_ORCHESTRA_h
#define AUTOMATIC_ORCHESTRA_h

//TODO refactor MIDI initialization, so this definition is dynamic
#define MIDI_CHANNEL 1

#include <Arduino.h>
#include <spi4teensy3.h>
#include "Sequencer.h"
#include "BodyseqSynth.h"
#include "MacAddress.h"

class AutomaticOrchestra {
public:
	AutomaticOrchestra();
	void init(int pMidiChannel, bool pIsKlockmeister, func_cb pCallback);
	void update();
	void triggerSequenceCallback();
private:
	String mMacAddress;
	int mSequenceID;
};

// TODO not sure if these methods are needed here for usbMIDI callbacks.
// See comment in implementation file for error.
///////////////////////////////////////////////////////////////////////
// THE BELOW FUNCTIONS ARE NEEDED FOR THE MUSIC PART TO RESPOND TO MIDI
// copied from CFO_PROTOSEQ.h
///////////////////////////////////////////////////////////////////////
/*
void OnNoteOn(byte channel, byte note, byte velocity) {
    if(channel == MIDI_CHANNEL) {
        Midi.noteOn(channel, note, velocity);
    }
    channel = channel - 1;
    MIDI_SERIAL.write(byte(0x90 | (channel & 0x0F)));
    MIDI_SERIAL.write(byte(0x7F & note));
    MIDI_SERIAL.write(byte(0x7F & velocity));
//    Serial.write("sent MIDI noteOn on MIDI OUT????");
}

void OnNoteOff(byte channel, byte note, byte velocity) {
    if(channel == MIDI_CHANNEL) {
        Midi.noteOff(channel, note, velocity);
    }
    channel = channel - 1;
    MIDI_SERIAL.write(byte(0x80 | (channel & 0x0F)));
    MIDI_SERIAL.write(byte(0x7F & note));
    MIDI_SERIAL.write(byte(0x7F & velocity));
}

void OnControlChange(byte channel, byte control, byte value) {
    if(channel == MIDI_CHANNEL) {
        Midi.controller(channel, control, value);
    }
    channel = channel - 1;
    MIDI_SERIAL.write(byte(0xB0 | (channel & 0x0F)));
    MIDI_SERIAL.write(byte(0x7F & control));
    MIDI_SERIAL.write(byte(0x7F & value));
}

void RealTimeSystem(byte realtimebyte) {
    Midi.midiRealTimeHandler(realtimebyte);
}
*/
///////////////////////////////////////////////////////////////////////
// END of copied functions
///////////////////////////////////////////////////////////////////////

#endif