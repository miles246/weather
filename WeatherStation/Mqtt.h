#ifndef MQTT_H
#define MQTT_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
#include <PubSubClient.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>
//const char* mqtt_server = "192.168.68.168";
//float temp;
//float pressure;
//float humidity;

void callback(char* topic, byte* payload, unsigned int length);
void connect_mqtt();
void recon();
void reconnect();
void publish_mqtt(float temp,float pressure,float humidity, float full, float ir, float vis, float mpsas, float dmpsas, float mlx_temp_amb, float mlx_temp_obj, float uv_vis, float uv_ir, float uv_indx);

#endif 
