#include <SparkFun_LPS25HB_Arduino_Library.h>
#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>

LPS25HB sensor;
OpenLog SDcard;  //Create instance
const String FILENAME = "rocketdata.txt";
int myLog;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensor.begin();

  if (sensor.isConnected() == false) {
    Serial.println("Seonsor hasn't been read.");

    while (1)
      ;
  }
}


void loop() {
  Serial.print("Current pressure: ");
  Serial.print(sensor.getPressure_hPa());
  Serial.print(", Current Tmeperature (°C): ");
  Serial.println(sensor.getTemperature_degC()); //The serial print is showing us the values on a screen 

  SDcard.print("Current pressure: ");
  SDcard.print(sensor.getPressure_hPa());
  SDcard.print(", Current Tmeperature (°C): ");
  SDcard.println(sensor.getTemperature_degC()); // the myLog is saving the values to the SD card 

  delay(40); //every 40 milliseconds the task repeats itself, giving us new values.
}


// got the two codes
