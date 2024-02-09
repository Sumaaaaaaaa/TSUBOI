#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("start");
}

void loop() {
  if(Serial.available())
  {
    Wire.beginTransmission(0x04);
    char a = Serial.read();
    Wire.write(a);
    int result = Wire.endTransmission();
    Serial.print(int(a));
    Serial.print("...");
    Serial.println(result);
  }

}
