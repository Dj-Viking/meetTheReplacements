#include <usbmidi.h>

// https://github.com/BlokasLabs/USBMIDI/blob/master/examples/midictrl/midictrl.ino

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(31250); // MIDI baudrate
}

void loop()
{
  // put your main code here, to run repeatedly:
  // Handle USB communication
  USBMIDI.poll();

  // Forward MIDI
  while (USBMIDI.available())
    Serial.write(USBMIDI.read());
  Serial.flush();
  while (Serial.available())
    USBMIDI.write(Serial.read());
  USBMIDI.flush();
}
