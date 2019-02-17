/* Reads the data from serial 2 (RX=17 TX=16) at 9600 and send to serial(0) at 115200 (RX, TX on board Wemos D1 mini32 V1.0.0)
*/

#include <Arduino.h>

void setup()
{
    // initialize both serial ports:
    Serial.begin(115200);
    Serial2.begin(9600);
    Serial.print("Init done");
}

void loop()
{
    // read from port 1, send to port 0:
    if (Serial2.available())
    {
        int inByte = Serial2.read();
        Serial.write(inByte);

    }

}