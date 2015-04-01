/**
 * @file    AutomaticOrchestra
 * @author  David Beermann
 * @date    03/31/2015
 * @version 0.1
 * 
 * @brief Wrapper for the ProtoSeq implemantion.
 */

#include "AutomaticOrchestra.h"


AutomaticOrchestra::AutomaticOrchestra() {
	mMacAddress = MacAddress::get();

	// create member array and load corresponding data set
	orchestra_member_t* mOrchestraMembers = new orchestra_member_t[OrchestraMemberConfig::MEMBER_COUNT];
	OrchestraMemberConfig::getDefaultConfig(mOrchestraMembers);

	// parse member array for matching configuration based on the device's MAC address
	for( unsigned int i = 0; i < OrchestraMemberConfig::MEMBER_COUNT; i++ ) {
		if( mMacAddress.equals(mOrchestraMembers[i].macAddress) ) {
			mMidiChannel = mOrchestraMembers[i].midiChannel;
			mKlockmeister = mOrchestraMembers[i].klockMeister;
			break;
		}
	}
}

const String AutomaticOrchestra::getMacAddress() {
	return mMacAddress;
}

const int AutomaticOrchestra::getMidiChannel() {
	return mMidiChannel;
}

const bool AutomaticOrchestra::isKlockmeister() {
	return mKlockmeister;
}

void AutomaticOrchestra::handleSequencerTick(){
	Serial.println("handleSequencerTick()");
}

void AutomaticOrchestra::handleNoteOn(byte channel, byte note, byte velocity){
	if(channel == mMidiChannel) {
        Midi.noteOn(channel, note, velocity);
    }
    channel = channel - 1;
    MIDI_SERIAL.write(byte(0x90 | (channel & 0x0F)));
    MIDI_SERIAL.write(byte(0x7F & note));
    MIDI_SERIAL.write(byte(0x7F & velocity));
}

void AutomaticOrchestra::handleNoteOff(byte channel, byte note, byte velocity){
	if(channel == mMidiChannel) {
        Midi.noteOff(channel, note, velocity);
    }
    channel = channel - 1;
    MIDI_SERIAL.write(byte(0x80 | (channel & 0x0F)));
    MIDI_SERIAL.write(byte(0x7F & note));
    MIDI_SERIAL.write(byte(0x7F & velocity));
}

void AutomaticOrchestra::handleControlChange(byte channel, byte control, byte value){
	if(channel == mMidiChannel) {
        Midi.controller(channel, control, value);
    }
    channel = channel - 1;
    MIDI_SERIAL.write(byte(0xB0 | (channel & 0x0F)));
    MIDI_SERIAL.write(byte(0x7F & control));
    MIDI_SERIAL.write(byte(0x7F & value));
}


