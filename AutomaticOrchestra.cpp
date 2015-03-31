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
	mOrchestraMembers = new orchestra_member_t[OrchestraMemberConfig::MEMBER_COUNT];
	OrchestraMemberConfig::getDefaultConfig(mOrchestraMembers);
}

void AutomaticOrchestra::init(func_cb pCallback){
	Serial.print("MAC Address: ");
	Serial.println(mMacAddress);

	// parse member array for matching configuration based on the device's MAC address
	for( unsigned int i = 0; i < OrchestraMemberConfig::MEMBER_COUNT; i++ ) {
		if( mMacAddress.equals(mOrchestraMembers[i].macAddress) ) {
			mConfig = &mOrchestraMembers[i];
			break;
		}
	}

	if( mConfig == NULL ) {
		Serial.print("ERROR: No configuration found for mac address ");
		Serial.println(mMacAddress);
	} else {
		Serial.print("MIDI Channel: ");
		Serial.println(mConfig -> midiChannel);
		Serial.print("Klock Meister: ");
		Serial.println(mConfig -> klockMeister);
	}

	Music.init();
	Music.enableEnvelope1();
	Music.enableEnvelope2();
	Music.getPreset(13);

	/*
	// TODO Where's the usbMIDI implementation/instanticiation happening?! No matter what I do I alwas get this error: 'usbMIDI' was not declared in this scope
	// These guys just have to be here...
	usbMIDI.setHandleNoteOff(OnNoteOff);
	usbMIDI.setHandleNoteOn(OnNoteOn);
	usbMIDI.setHandleControlChange(OnControlChange);
	usbMIDI.setHandleRealTimeSystem(RealTimeSystem);
	*/

	analogReadAveraging(32);

	Sequencer.init(140);

	mSequenceID = Sequencer.newSequence(NOTE_16, pCallback);
	Sequencer.startSequence(mSequenceID);

	// Klockmeister/Slave initialization
	Midi.setMidiIn(false);
	Midi.setMidiThru(false);
	Midi.setMidiOut(false);
	Midi.setMidiClockIn(!mConfig -> klockMeister);
	Midi.setMidiClockThru(!mConfig -> klockMeister);
	Midi.setMidiClockOut(mConfig -> klockMeister);
	Sequencer.setInternalClock(mConfig -> klockMeister);

	//TODO remove when #define MIDI_CHANNEL is refactored
	// implementation to be tested...
	//Midi.setChannel(mConfig -> midiChannel);
}

void AutomaticOrchestra::update() {
	Sequencer.update();
	//usbMIDI.read();
	Midi.checkSerialMidi();
}

void AutomaticOrchestra::triggerSequenceCallback(){
	//Serial.println("AutomaticOrchestra::triggerSequenceCallback()");
}