#define MIDI_CHANNEL 1

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <CFO_PROTOSEQ.h>

// sequence ID
int s1, s2;

int notes1[] = {36, 48, 36, 48, 36, 48, 36, 48};
int notes2[] = {76, 43, 49, 78};

void setup() {
  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();

  Music.enableEnvelope1();
  Music.enableEnvelope2();
  Music.getPreset(8);

// These guys just have to be here...
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem);
  
//  analogReadAveraging(32);

  Sequencer.init(140);
  Sequencer.setInternalClock(true);


  s1 = Sequencer.newSequence(NOTE_16, 8, LOOP);
  Sequencer.insertNotes(s1, notes1, 4, 0);
  Sequencer.insertNotes(s1, notes2, 4, 5);
  
  Sequencer.startSequence(s1);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Sequencer.update();
  usbMIDI.read();

}




