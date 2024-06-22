#include "Arduino.h"
#include "pins_arduino.h"

int datapin = 6;
int interruptpin = 2;

byte status_byte = 0x0;

void
inter_handler()
{

  // status byte for program change on channel 2
  // 0x1100 <- status with kind
  // 0x0002 <- channel
  status_byte = B11000010;
  byte data_byte = B00101100;

  // maybe send 0xee ??? which is the status byte and the data_byte added together
  // unless you have to send status before data byte? 

  digitalWrite(datapin, status_byte);
  digitalWrite(datapin, data_byte);
}

void setup()
{

  // put your setup code here, to run once:
  Serial.begin(31250); // MIDI baudrate

  // set up pins
  pinMode(datapin, OUTPUT);
  pinMode(interruptpin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptpin), inter_handler, RISING);
}

void loop()
{

  for (int i = 0; i < 10; i++)
  {
    Serial.write("what the fuckkkk\n");
  }
}
