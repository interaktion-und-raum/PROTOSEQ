#define MIDI_CHANNEL 1

#include <spi4teensy3.h>
#include <EEPROM.h>
#include <CFO_PROTOSEQ.h>


void setup() {
  // We initialise the sound engine by calling Music.init() which outputs a tone
  Music.init();
  Music.getPreset(0);
  Music.enableEnvelope1();
  Music.enableEnvelope2();
    
// These guys just have to be here...
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandleRealTimeSystem(RealTimeSystem);
}

void loop() {
// Checking for incoming MIDI to use dashboard
  usbMIDI.read();

}
