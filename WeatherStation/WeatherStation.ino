#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include "Wifi.h"
#include "Mqtt.h"
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
//---------TSL2591---------
#include "SQM_TSL2591.h"

SQM_TSL2591 sqm = SQM_TSL2591(2591);
void readSQM(void);
//----------UV-----------------
#include "Adafruit_SI1145.h"
Adafruit_SI1145 uv = Adafruit_SI1145();

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;

Adafruit_BME280 bme;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();


void setup() {
  Serial.begin(115200);
  while (!Serial);

  setup_wifi();
  connect_mqtt();
  if (sqm.begin()) {

    Serial.println("Found SQM (TSL) sensor");
    sqm.config.gain = TSL2591_GAIN_LOW;
    sqm.config.time = TSL2591_INTEGRATIONTIME_200MS;
    sqm.configSensor();
    sqm.showConfig();
    sqm.setCalibrationOffset(0.0);
  } else{
    Serial.println("SQM sensor not found");
 }
  mlx.begin(); 
}

void loop() {
  recon();
  long now = millis();
  sqm.takeReading();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    float temp = bme.readTemperature();
    float pressure = bme.readPressure()/100.0;
    float humidity = bme.readHumidity();
    float full = sqm.full;
    float ir = sqm.ir;
    float vis = sqm.vis;
    float mpsas = sqm.mpsas;
    float dmpsas = sqm.dmpsas;
    float mlx_temp_amb = mlx.readAmbientTempC();
    float mlx_temp_obj = mlx.readObjectTempC();
    float uv_vis = uv.readVisible();
    float uv_ir = uv.readIR();
    float uv_indx = uv.readUV()/100.0;

    publish_mqtt(temp,pressure,humidity, full, ir, vis, mpsas, dmpsas, mlx_temp_amb, mlx_temp_obj, uv_vis,  uv_ir,  uv_indx);

  }
    
}
