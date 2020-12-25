#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SparkFun_TMP117.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <Secret.h> // WiFi logins

#define NB_LIGNE 50
#define STRING_SIZE 100

#define SDA_PIN D1
#define SCL_PIN D2
#define i2C_CLOCK 400000

const char* ssid = myssid;
const char* password = mypasswd;

char myindex[NB_LIGNE][STRING_SIZE]; 
String mystr = "";

char uptime[64];
char temp[64] = "22.051263";

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
}

void loop() {
  int iuptime = (int) millis() / 1000;
  snprintf(uptime,sizeof(uptime), "%d", iuptime);
  delay(500);
  generate_exporter();
  Serial.println("Gawr Gura");

}


void setup_wifi() {
  delay(3);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void generate_exporter() {
  mystr = "";
  strcpy(myindex[0], "# TYPE nodemcu_uptime_seconds gauge\n");
  strcpy(myindex[1], "nodemcu_uptime_seconds ");
  strcpy(myindex[2], uptime);

  strcpy(myindex[3], "\n# TYPE nodemcu_tmp117_temp gauge\n");
  strcpy(myindex[4], "nodemcu_tmp117_temp ");
  strcpy(myindex[5], temp);
  strcpy(myindex[6], "\n");

  for(int i = 0; i < 7; ++i) {
    mystr += myindex[i];
  }
}

void SensorInit() {
  bool sensor_init = false;
  sensor_init = sensor.begin();
  
  while (sensor_init != true) {
    Serial.println("TMP117 not initialised, retry");
    sensor_init = sensor.begin();
  }
  
  if (sensor_init == true) {
    Serial.println("TMP117 initialised");
  }
}

const char* SensorData() {
  double tempC = 0.0;
  char sTempC[64];
  if (sensor.dataReady() == true) {
    tempC = sensor.readTempC();
    dtostrf(tempC, 11, 7, sTempC);
    return sTempC;
  }
  else
    return "-1";
}