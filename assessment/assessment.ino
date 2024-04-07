//we are including the 3 libraries so that we can
#include <SparkFun_LPS25HB_Arduino_Library.h>  
#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>

LPS25HB sensor;                               //TEACHER COMMENTS what is this for?
OpenLog SDcard;                            //Create instance/labeling the Log as SDcard
const String FILENAME = "rocketdata.txt";  //the FILENAME is being called/saved as rocketdata.txt
int myLog;  //TEACHER COMMENTS what is this for?

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensor.begin(); 

  //TEACHER COMMENTS what does this do?
  if (sensor.isConnected() == false) {
    Serial.println("Sensor hasn't been read.");
    while (1);
  }

  //TEACHER COMMENTS if you check the sensor is working why not the sdCard?

  
}


void loop() {
  //TEACHER COMMENTS what does this do?
  Serial.print("Current pressure: ");
  Serial.print(sensor.getPressure_hPa());
  Serial.print(", Current Tmeperature (°C): ");
  Serial.println(sensor.getTemperature_degC());  //The serial print is showing us the values on a screen

  //TEACHER COMMENTS what about these lines?
  SDcard.print("Current pressure: ");
  SDcard.print(sensor.getPressure_hPa());
  SDcard.print(", Current Tmeperature (°C): ");
  SDcard.println(sensor.getTemperature_degC());  // the myLog is saving the values to the SD card

  delay(40);  //every 40 milliseconds the task repeats itself, giving us new values.
}


// got the two codes
