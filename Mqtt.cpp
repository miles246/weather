#include "Mqtt.h"
#include "Wifi.h"
#include <Wire.h>
#include "Adafruit_SI1145.h"
Adafruit_SI1145 uv = Adafruit_SI1145();

WiFiClient espClient;
PubSubClient client(espClient); 
const char* mqtt_server = "192.168.68.138";

void callback(char* topic, byte* payload, unsigned int length) {

}
void connect_mqtt(){
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void recon(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
    Serial.println("mqtt okk");
  }
}
void publish_mqtt( float temp, float pressure, float humidity, float full, float ir, float vis, float mpsas, float dmpsas, float mlx_temp_amb, float mlx_temp_obj){
  //client.publish("/home/sensors", output);
    uint16_t uvvis = uv.readVisible();
    uint16_t uvuv = uv.readUV()/100.0;
    uint16_t uvir = uv.readIR();

    StaticJsonDocument<384> doc;
    char output[208];
    doc["t"] = temp;
    doc["p"] = pressure;
    doc["h"] = humidity;
    //-------TSL---------
    doc["f"] = full;
    doc["i"] = ir;
    doc["v"] = vis;
    doc["m"] = mpsas;
    doc["d"] = dmpsas;
    //-------MLX--------
    doc["mlx_temp_amb"] = mlx_temp_amb;
    doc["mlx_temp_obj"] = mlx_temp_obj;
    //------Uv------
    doc["uv_indx"] = uvuv;
    doc["uv_vis"] = uvvis ;
    doc["uv_ir"] = uvir;

    Serial.println("Read");

    serializeJson(doc, output);
    Serial.println(output);
    client.publish("/home/sensors", output);
    Serial.println("Sent");
}
