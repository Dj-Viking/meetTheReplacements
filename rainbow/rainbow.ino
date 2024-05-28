#include <Adafruit_WS2801.h>

/*!
 * @brief Empty constructor; init pins/strand length/data order later:
 */


void setup()
{
  Adafruit_WS2801 strip = Adafruit_WS2801();
  // TODO: find out the clock pin on the actual board
  strip.updatePins(6, 7);
  strip.updateLength(1);
  strip.updateOrder(WS2801_RGB);

  strip.begin();
  strip.show();
  Serial.begin(9600);
}

void loop()
{
  Serial.print("NO FORMAT");
}