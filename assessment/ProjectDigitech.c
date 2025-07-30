#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include "arduino_secrets.h"
#include <ESPAsyncWebServer.h>
#define SECRET_SSID "T8-Arduino"
#define SECRET_PASS "T8-Arduino"



const char SSID[] = SECRET_SSID;
const char PASSWORD[] = SECRET_PASS;

WifiServer server(80);

const byte LEDPIN = 13;
const byte SENSORPIN = A5;

*WiFi stuff

void initWiFi()
{
    WiFi.mode(WIFI_STA)
    Wifi.begin(SSID, PASSWORD);
    Serial.print('Connecting to WiFi ..');
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }
Serial.print("Connected to ");
Serial.println(SSID);

Serial,print("Use http://");
Serial.println(WiFi.localIP());
}

/************
 * Setup stuff
 ************/
void setup()
{

  pinMode(LEDPIN, OUTPUT);
  pinMode(SENSORPIN, INPUT);

  Serial.begin(115200);
  delay(5000); 

  initWWiFi();

  server.begin();
}

/************
 * loop stuff
 ************/
void loop()
{

  //check if anyone connects to the ESP32
  WiFiClient client = server.avaliable();
  if (client)
  {
    Serial.println("new client");
    //variable to hold any incoming data from the browser or client
    String currentLine = "";

    //while they are connected
    while (client.connected()) //check if server is avaliable/client has connected
    {
      if (client.avaliable())//while connected
      {
        //another variable to hold any incoming
        char c = client.read();
        Serial.write(c);

        /////////////////////////////
        //if browser sent a newline character
        if (c == '\n')
        {
          //if the current line is blank, you
          //that's the end of the client HTTP
          if (currentLine.length() == 0)
          {
            //HTTP code for a webpage after some initial set
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println("Refresh: 5"); //refresh
            client.println();
            client,println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<style>html{font-family: Arial}")

            client.println("<h1>Sensor stuff</h1>");
            //output the value of an analog input pin
            int sensorReading = analogRead(SENSORPIN);
            client.print("RAW Sensor value is "); //use
            client.print(sensorReading);

            //output different text depending on the LED value
            byte LEDReading = digitalRead(LEDPIN);
            if(LEDReading == HIGH){
              client.print("Red LED is on<br><br>");
            }else{
              client.print("Red LED is off<br><br>");
            }
            //when  you click either of these links you add a H or L into the
            //and that gets read by if statements below
            //below create the hyper links
            client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
            client.print("Click <a href=\"/L\">here</a> turn the LED off<br>");

            client.println("</html>");
            break; //leave the while loop
            }
            else
            {// if you got a first newline, then clear currentLine variable }
              currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c; //add to the end of the current line
        }
        if currentLine.endWith(("GET /H"))
        {
          digitalWrite(LEDPIN, HIGH); // GET /H turns the LED on
        }
        if (currentLine.endWith("GET /L"))
        {
          digitalWrite(LEDPIN, LOW); // GET /L turns the LED off
        }
      } //end of the client.avaliable
    }//end of while loop
    //close the connection at the ESP32 end as 
    //the client is not connected (see while loop above)
    client.stop();
    Serial.println("client disconnected");
  }//end of if client
}

[env:adafruit_feather_esp32s3_reversetft]
platform = espressif32
board = adafruit_feather_esp32s3_reversetft
framework = arduino
build_flags = 
-DARDUINO_USB_MODE=1
-DARDUINO_USB_CDC_ON_BOOT=1
mointor_speed = 115200
lib_compact_mode = strict 
lib_ldf_mode = chain+




\XSHAL_STRICT_CACHEATTR_BYPASSlib_ldf_mode = chain+

int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}