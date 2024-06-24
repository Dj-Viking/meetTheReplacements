#include "Arduino.h"
#include "pins_arduino.h"

int datapin = 6;

// analog pin
int analogpin = A0;

byte status_byte = B11000010;
byte data_byte = B00101100;

void setup()
{

  // put your setup code here, to run once:
  Serial.begin(31250); // MIDI baudrate

  // set up pins
  pinMode(datapin, OUTPUT);
  pinMode(analogpin, INPUT_PULLUP); // pulled high to start
}

void loop()
{

  Serial.print("DRAW\n");

  // TODO(Anders): figure out after I build the switch thing if I have to
  // read an analog pin for when it is LOW or HIGH
  // and then send the bytes down the data pin
  // hmmm

  Serial.print("analog pin reading\n");
  Serial.print(analogRead(analogpin));
  int tolerance = 0.13;
  // analog input is started with pulled high.
  // the switch is pulling it low with 220ohm to ground
  while(analogRead(analogpin) <= (21 + tolerance)) {
    Serial.print("\nSEND THE MIDI NOWWWWWW\n");
    Serial.print("\n");
    Serial.print("\n");
    delay(1);
  }
  Serial.print("\n");
  delay(100);
  Serial.print("\n");
  Serial.print("===================\n");
  /**
   * if (readpin(analogpin) === HIGH) {
   *     digitalWrite(datapin, status_byte);
   *     digitalWrite(datapin, data_byte);
   * }
   */
}
