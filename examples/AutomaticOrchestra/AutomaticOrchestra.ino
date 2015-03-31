/**
 * @file    AutomaticOrchestra.ino
 * @author  David Beermann
 * @date    03/31/2015
 * @version 1.0
 * 
 * @brief This Arduino project should be the starting point for any implementation of
 * the Automatic Orchestra installation.
 */

// Libraries originally intended to be stored in AutomaticOrchestra class.
// Due to an Arduino IDE inherent drawback, the libraries need to be defined here,
// to be available for the linker during compilation. See here:
// http://provideyourown.com/2011/advanced-arduino-including-multiple-libraries/
#include <spi4teensy3.h>
#include <EEPROM.h>
// Actual include of the project library
#include <AutomaticOrchestra.h>

AutomaticOrchestra* ao = new AutomaticOrchestra();


void setup() {
  // wait for 'whatever' happens when including the libraries.
  // without delay no serial output send in the setup() method will be printed.
  delay(1000);

  Serial.begin(9600);
  Serial.println("setup()");
  
  ao->init();
}

void loop() {
}
