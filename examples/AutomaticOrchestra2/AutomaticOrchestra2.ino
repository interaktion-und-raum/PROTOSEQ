#define MIDI_CHANNEL 1

#include <spi4teensy3.h>
#include <EEPROM.h>
#include "Sequencer.h"
#include "BodyseqSynth.h"
#include "AutomaticOrchestra.h"


// entry point for the installation
AutomaticOrchestra* ao = new AutomaticOrchestra();

// sequence ID
int mSequenceID;


void setup(){
	// wait for 'whatever' happens when including the libraries.
	// without delay no serial output send in the setup() method will be printed.
	delay(2000);

	Serial.begin(9600);
	Serial.println("setup()");
	Serial.print("isKlockmeister:");
	Serial.println(ao -> isKlockmeister());

	// We initialise the sound engine by calling Music.init() which outputs a tone
	Music.init();
	Music.enableEnvelope1();
	Music.enableEnvelope2();
	Music.getPreset(13);

	// These things just have to be here...
	usbMIDI.setHandleNoteOff(OnNoteOff);
	usbMIDI.setHandleNoteOn(OnNoteOn);
	usbMIDI.setHandleControlChange(OnControlChange);
	usbMIDI.setHandleRealTimeSystem(RealTimeSystem);

	analogReadAveraging(32);

	Sequencer.init(140);

	mSequenceID = Sequencer.newSequence(NOTE_16, &OnSequencerTick);
	//Sequencer.insertNotes(mSequenceID, notes1, 16, 0);
	//Sequencer.setInternal(mSequenceID, true);
	//Sequencer.setExternal(mSequenceID, false);
	Sequencer.startSequence(mSequenceID);

	Midi.setMidiIn(false);
	Midi.setMidiThru(false);
	Midi.setMidiOut(false);
	Midi.setMidiClockIn(false);
	Midi.setMidiClockThru(true);
	Midi.setMidiClockOut(false);
	Sequencer.setInternalClock(true);
}

void loop() {
	Serial.println("loop()");
	Sequencer.update();
	usbMIDI.read();
	Midi.checkSerialMidi();
}

void OnSequencerTick() {
	Serial.println("OnSequencerTick()");
	ao -> handleSequencerTick();
}

void OnNoteOn(byte channel, byte note, byte velocity) {
	ao -> handleNoteOn( channel, note, velocity );
}

void OnNoteOff(byte channel, byte note, byte velocity) {
	ao -> handleNoteOff( channel, note, velocity );
}

void OnControlChange(byte channel, byte control, byte value) {
    ao -> handleControlChange( channel, control, value );
}

void RealTimeSystem(byte realtimebyte) {
    Midi.midiRealTimeHandler(realtimebyte);
}
