#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SparkFun_TMP117.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <Secret.h> // WiFi logins

#define NB_LIGNE 50
#define STRING_SIZE 100
#define TIMER 1000 // Each loop in ms

#define SDA_PIN D1
#define SCL_PIN D2
#define ANALOG_PIN A0 // Testing TEMP DELETE
#define i2C_CLOCK 400000 // i2C Fast mode


const char* ssid = myssid; // In ../lib/Secret/Secret.h Exemple: const char* myssid = "wifi_ssid";
const char* password = mypasswd; // In ../lib/Secret/Secret.h Exemple: const char* myssid = "wifi_password";
const char* hostname = "prom117"; //DHCP Hostname

char myindex[NB_LIGNE][STRING_SIZE]; 
String mystr = "";

char uptime[64];
char temp[64] = "22.051263";
int analogValue = 0.0; // Testing TEMP DELETE

bool staticValue = false; // Static strings, Generated once, ( I don't want them in setup() )
bool b_sensor_init = false;

unsigned long now = 0;
unsigned long last = 0;

// Prototype
void setup_wifi();
void generate_exporter();
void sensor_init();
const char* sensor_data();

AsyncWebServer server(9100);
TMP117 sensor;


void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(i2C_CLOCK);
  setup_wifi();
  server.on("/metrics", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", mystr);
});
  server.begin();
  sensor_init();
}

void loop() {
  now = millis();
  if(now - last > TIMER) {
    if(WiFi.status() == WL_CONNECTED){
      last = now;
      int intUptime = (int) millis() / 1000;
      snprintf(uptime,sizeof(uptime), "%d", intUptime); // Update uptime
      analogValue = analogRead(ANALOG_PIN); // Testing TEMP DELETE
      sniprintf(temp, sizeof(temp), "%d", analogValue); // Testing TEMP DELETE
      generate_exporter();
      Serial.println(mystr);
    }
    else if(WiFi.status() != WL_CONNECTED) {
      setup_wifi();
    }
  }
}


void setup_wifi() {
  delay(3);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  if(WiFi.hostname(hostname)) {
    Serial.println("Hostname: ");
    Serial.println(hostname);
  }
  

}

void generate_exporter() {
  mystr = "";
  if(!staticValue) {
    strcpy(myindex[0], "# TYPE nodemcu_uptime_seconds gauge\n");
    strcpy(myindex[1], "nodemcu_uptime_seconds ");

    strcpy(myindex[3], "\n# TYPE nodemcu_tmp117_temp gauge\n");
    strcpy(myindex[4], "nodemcu_tmp117_temp ");
    strcpy(myindex[6], "\n");

    Serial.println("staticValue generated");
    staticValue = true;
  }

  strcpy(myindex[2], uptime);
  strcpy(myindex[5], temp);

  for(int i = 0; i < 7; ++i) {
    mystr += myindex[i];
  }
}

void sensor_init() {
  b_sensor_init = sensor.begin();
  
  while (!b_sensor_init) {
      Serial.println("TMP117 not initialised, retry in 10s");
      delay(10000);
  }
  
  if (b_sensor_init) {
    Serial.println("TMP117 initialised");
  }
}

const char* SensorData() {
  double tempC = 0.0;
  char sTempC[64];
  if (sensor.dataReady() == true) { //Should always return true if the sensor is in Continuous Conversion Mode
    tempC = sensor.readTempC();
    snprintf(sTempC,sizeof(sTempC), "%f", tempC);
    return sTempC;
  }
  else
    return "-1";
}
