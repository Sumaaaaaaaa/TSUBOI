#include <Arduino.h>

#include <Wire.h>

#include <FastLED.h>
const int numLeds = 70; // LEDの数
const byte dataPin = 4; // LEDデータピン
CRGB leds[numLeds]; // LED配列
CRGB originalColor = CRGB::Black; // フリッカー効果用の元の色

const int startUniverseColor = 0; // RGBカラー情報のユニバース
const int startUniverseFlicker = 1; // フリッカー情報のユニバース

//unsigned long flickerSpeed = 0; // フリッカー速度（初期値は0、フリッカー無し）
int flickerSpeed = 0; 
unsigned long lastFlickerTime = 0; // 前回のフリッカー時間
bool ledsOff = false; // LEDが消灯しているかどうかのフラグ

void setup() {

  Wire.begin(0X04);
  Wire.onReceive(receiveEvent); 
  
  //Serial.begin(9600);

  FastLED.addLeds<WS2812, dataPin, GRB>(leds, numLeds);
  fill_solid(leds, numLeds, originalColor);
  FastLED.show();

  Serial.println("SystemStarted...");
  
}

void loop() 
{
  //Serial.println(int(ledsOff));
  
  unsigned long currentTime = millis();

  // フリッカーが有効な場合、フリッカー効果を適用
  if (flickerSpeed > 0 && currentTime - lastFlickerTime >= flickerSpeed) 
  {
    if (ledsOff) {
      fill_solid(leds, numLeds, originalColor); // 元の色に戻す
      ledsOff = false;
    } else {
      fill_solid(leds, numLeds, CRGB::Black); // 消灯させる
      ledsOff = true;
    }
    FastLED.show();
    lastFlickerTime = currentTime;
  }
  if (flickerSpeed == 0)
  {
    fill_solid(leds, numLeds, originalColor); // 元の色に戻す
    FastLED.show();
  }
  delay(1);
}

void receiveEvent(int howMany)
{
  while (Wire.available()) { // loop through all
  char c = Wire.read(); // receive byte as a character
  flickerSpeed = int(c);
  }
}
