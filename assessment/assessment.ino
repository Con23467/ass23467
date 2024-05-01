//we are including the 3 libraries so that we can
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>

LPS25HB sensor;                            //The LPS25HB is a pressure sensor wich functions as a digital output barometer
OpenLog SDcard;                            //Create instance/labeling the Log as SDcard
const String FILENAME = "rocketdata.txt";  //the FILENAME is being called/saved as rocketdata.txt
int myLog;                                 //TEACHER COMMENTS what is this for?

void setup() {
  Serial.begin(9600);  //This tells the arduino to get ready to connect to the serial monitor
  Wire.begin();        //initialises the wire library and joins the I2C bus as a controller. 
  sensor.begin();
  SDcard.begin();
delay(1000);
  //TEACHER COMMENTS what does this do?
  if (sensor.isConnected() == false) {
    Serial.println("Sensor hasn't been read.");
    while (1)
      ;
  }

  //TEACHER COMMENTS if you check the sensor is working why not the sdCard?
} 



void loop() {
  //the void loop is being used to loop (repeat) the code in the loop ({}) with the serial monitor printing out the pressure and temperature values. The loop is bing used to repeatedly remeausre the values.
  Serial.print("Current pressure: ");
  Serial.print(sensor.getPressure_hPa());
  Serial.print(", Current Tmeperature (°C): ");
  Serial.println(sensor.getTemperature_degC());  //The serial print is showing us the values on a screen

  //the SDcard print and println is writing out the values for the pressure andn temperature then saving it to the SD card.
  SDcard.print("Current pressure: ");
  SDcard.print(sensor.getPressure_hPa());
  SDcard.print(", Current Tmeperature (°C): ");
  SDcard.println(sensor.getTemperature_degC());  // the myLog is saving the values to the SD card

  delay(40);  //every 40 milliseconds the task repeats itself, giving us new values.
}



// got the two codes