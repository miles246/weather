class Mqtt2 {

  private:


    const char* _mqtt_server;
    WiFiClient espClient;
    PubSubClient client(espClient);
    unsigned long lastMsg = 0;
    #define MSG_BUFFER_SIZE  (50)
    char msg[MSG_BUFFER_SIZE];
    int value = 0;


  public:

    void callback(char* topic, byte* payload, unsigned int length) { }

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
      }
    }


};
Mqtt2 Mqtt2;
