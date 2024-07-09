#include <ADSWeather.h>
#include <ArduinoJson.h>
#include <DHT.h>

#include "WeatherInfo.h"

#define rainPin 4
#define wdPin 2
#define wsPin 2
#define dhtPin 15

#define CALC_INTERVAL 1000

unsigned long nextCalc;
unsigned long timer;
ADSWeather ws1(RAIN_PIN, VANE_PIN, ANEMOMETER_PIN);
DHT dht(dhtPin, DHT22);
WeatherInfo KuyaKin;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(rainPin), ws1.countRain, FALLING);
  attachInterrupt(digitalPinToInterrupt(wdPin), ws1.countAnemometer, FALLING);
  nextCalc = millis() + CALC_INTERVAL;
  dht.begin();
}

void loop() {
  timer = millis();
  int rainAmmount;
  long windSpeed;
  long windDirection;
  int windGust;
  float temperature;
  float humidity;

  ws1.update();
  if (timer > nextCalc) {
    nextCalc = timer + CALC_INTERVAL;

    KuyaKim.updateValues(&ws1, & dht);
  }
}
