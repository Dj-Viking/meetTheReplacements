#include "Arduino.h"
#include "pins_arduino.h"

int datapin = 6;

// analog pin
int analogpin = 5; // not sure yet

byte status_byte = B00000000;
byte data_byte = B00101100;

void setup()
{

  // put your setup code here, to run once:
  Serial.begin(31250); // MIDI baudrate

  // set up pins
  pinMode(datapin, OUTPUT);
  // pinMode(interruptpin, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(interruptpin), inter_handler, RISING);
}

void loop()
{

  Serial.print("DRAW\n");

  // TODO(Anders): figure out after I build the switch thing if I have to
  // read an analog pin for when it is LOW or HIGH
  // and then send the bytes down the data pin
  // hmmm

  /**
   * if (readpin(analogpin) === HIGH) {
   *     digitalWrite(datapin, status_byte);
   *     digitalWrite(datapin, data_byte);
   * }
   */
}
