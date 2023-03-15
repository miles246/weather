class Wifi2 {

  private:


    const char* _ssid;
    const char* _password;


  public:

    void setup_wifi(const char* _ssid, const char* _password) {
      _ssid = ssid;
      _password= password;
      delay(100);
      // We start by connecting to a WiFi network
      Serial.println();
      Serial.print("Connecting to ");
      Serial.println(ssid);
    
      WiFi.init(AP_STA_MODE);
      WiFi.begin(ssid, password);
    
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
    
      randomSeed(micros());
    
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());


};
Wifi2 Wifi2;
