#include Arduino.h
#include "ArduinoJson.h"
#include "WiFi.h"
#include "arduino_secrets.h"

#define AHTPIN 2
#define AHTTYPE AHT20  // Change to DHT11 if needed
#define FAN_PIN 5
#define HEATER_LED_PIN 6

// Humidity thresholds
#define HUMIDITY_HIGH 70.0  // Over this, fan runs faster
#define HUMIDITY_LOW  50.0  // Below this, heater/LED turns on


const char* ssid = "T8-Arduino"; 
const char* password = "T8-Arduino";

AsyncWebServer server(80);
const byte LEDPIN = 2; // GPIO pin for the LED
String ledState;


void initLittleFS()
{
  if (!LittleFS.begin(true)) 
  {
    Serial.println("LittleFS Mount Failed");
    return;
  }
  else 
  {

  Serial.println("LittleFS Mounted Successfully");
  }
}
void initWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Use this IP in your browser:");
  Serial.println(WiFi.localIP());
  Serial.println("Connected to WiFi");
}
  String processor(const String &VAR)
  {
    if (VAR == "STATE")
    {
      if (digitalRead(LEDPIN) == HIGH)
      {
        ledState = "ON";
      }
      else
      {
        ledState = "OFF";
      }
      return ledState;
    }
    return String();
  }
void setup()
{ 
  Serial.begin(115200);
  while(!Serial) 
  {
    delay(100);
  }
  initWiFi();
  initLittleFS();
  pinMode(LEDPIN, OUTPUT);
}
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) 
{
  request->send(LittleFS, "/index.html", "text/html", false, processor);
});
false, processor); });

server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) 
{
  digitalWrite(LEDPIN, LOW);
  request->send(LittleFS, "/index.html", "text/html", false, processor);
;
false, processor); });

server.begin();
}
void loop()
{
  // Nothing to do here
}