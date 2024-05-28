#include <Adafruit_WS2801.h>

/*!
 * @brief Empty constructor; init pins/strand length/data order later:
 */

auto strip = Adafruit_WS2801();

void setup()
{
    strip.begin();
    strip.show();
    Serial.begin(9600);
}

void loop()
{
    Serial.print("NO FORMAT");
}