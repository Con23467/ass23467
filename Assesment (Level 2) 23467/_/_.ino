#include <SparkFun_LPS25HB_Arduino_Library.h> 

LPS25HB sensor; 

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  sensor.begin(); 

  if (sensor.isConnected() == false) 
  {
    Serial.println("Seonsor hasn't been read.");  
  
    while (1)
      ;
  }
}

void loop()
{
  Serial.print("Current pressure: ");
  Serial.print(sensor.getPressure_hPa()); 
  Serial.print(", Current Tmeperature (°C): ");
  Serial.println(sensor.getTemperature_degC()); 

  delay(40); 
}


// got the two codes 


#include <SparkFun_LPS25HB_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_LPS25HB

LPS25HB pressureSensor; // Create an object of the LPS25HB class

void setup()
{
  Serial.begin(9600);
  Serial.println("LPS25HB Pressure Sensor Example 1 - Basic Readings");
  Serial.println();

  Wire.begin();
  pressureSensor.begin(); // Begin links an I2C port and I2C address to the sensor, sets an I2C speed, begins I2C on the main board, and then sets default settings

  if (pressureSensor.isConnected() == false) // The library supports some different error codes such as "DISCONNECTED"
  {
    Serial.println("LPS25HB disconnected. Reset the board to try again.");     // Alert the user that the device cannot be reached
    Serial.println("Are you using the right Wire port and I2C address?");      // Suggest possible fixes
    Serial.println("See Example2_I2C_Configuration for how to change these."); // Suggest possible fixes
    Serial.println("");
    while (1)
      ;
  }
}

void loop()
{
  Serial.print("Pressure in hPa: ");
  Serial.print(pressureSensor.getPressure_hPa()); // Get the pressure reading in hPa
  Serial.print(", Temperature (degC): ");
  Serial.println(pressureSensor.getTemperature_degC()); // Get the temperature in degrees C

  delay(40); // Wait - 40 ms corresponds to the maximum update rate of the sensor (25 Hz)
}
