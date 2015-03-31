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
}

void AutomaticOrchestra::init(int pMidiChannel, bool pIsKlockmeister, func_cb pCallback){
	Serial.print("AutomaticOrchestra::init() -- midi channel: ");
	Serial.print(pMidiChannel);
	Serial.print(" -- klock meister: ");
	Serial.println(pIsKlockmeister);

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
	Midi.setMidiClockIn(!pIsKlockmeister);
	Midi.setMidiClockThru(!pIsKlockmeister);
	Midi.setMidiClockOut(pIsKlockmeister);
	Sequencer.setInternalClock(pIsKlockmeister);
}

void AutomaticOrchestra::update() {
	Sequencer.update();
	//usbMIDI.read();
	Midi.checkSerialMidi();
}

void AutomaticOrchestra::triggerSequenceCallback(){
	Serial.println("AutomaticOrchestra::triggerSequenceCallback()");
}