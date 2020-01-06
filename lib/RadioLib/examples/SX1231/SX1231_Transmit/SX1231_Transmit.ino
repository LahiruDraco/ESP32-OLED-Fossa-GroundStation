/*
   RadioLib SX1231 Transmit Example

   This example transmits packets using SX1231 FSK radio module.

   NOTE: SX1231 offers the same features as RF69 and has the same
         interface. Please see RF69 examples for examples on AES,
         address filtering, interrupts and settings.

   For full API reference, see the GitHub Pages
   https://jgromes.github.io/RadioLib/
*/

// include the library
#include <RadioLib.h>

// SX1231 has the following connections:
// CS pin:    10
// DIO0 pin:  2
// RESET pin: 3
SX1231 rf = new Module(10, 2, 3);

// or using RadioShield
// https://github.com/jgromes/RadioShield
//SX1231 rf = RadioShield.ModuleA;

void setup() {
  Serial.begin(9600);

  // initialize SX1231 with default settings
  Serial.print(F("[SX1231] Initializing ... "));
  // carrier frequency:                   434.0 MHz
  // bit rate:                            48.0 kbps
  // Rx bandwidth:                        125.0 kHz
  // frequency deviation:                 50.0 kHz
  // output power:                        13 dBm
  // sync word:                           0x2D01
  int state = rf.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

void loop() {
  Serial.print(F("[SX1231] Transmitting packet ... "));

  // you can transmit C-string or Arduino string up to 256 characters long
  int state = rf.transmit("Hello World!");

  // you can also transmit byte array up to 256 bytes long
  /*
    byte byteArr[] = {0x01, 0x23, 0x45, 0x56, 0x78, 0xAB, 0xCD, 0xEF};
    int state = rf.transmit(byteArr, 8);
  */

  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F(" success!"));

  } else if (state == ERR_PACKET_TOO_LONG) {
    // the supplied packet was longer than 256 bytes
    Serial.println(F(" too long!"));

  }

  // wait for a second before transmitting again
  delay(1000);
}
