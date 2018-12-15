#include "ACS712.h"
char watt[5];
ACS712 sensor(ACS712_30A, A0);
unsigned long last_time = 0;
unsigned long current_time = 0;
float Wh;
void setup()
{
  Serial.begin(115200);
  sensor.calibrate();
}

void loop()
{
  float V = 230.0;
  float I = sensor.getCurrentAC();
  //Serial.println(I);
  float P = (V * I) / 1.85;
  last_time = current_time;
  current_time = millis();
  Wh = Wh + P * ((current_time - last_time) / 3600000.0);
  Wh = Wh - 0.0025;
 // bill_amount = Wh * (energyTariff/1000);
  dtostrf(Wh, 4, 2, watt);
  Serial.println(watt);
  Serial.write(watt);
  delay(1000);
}
