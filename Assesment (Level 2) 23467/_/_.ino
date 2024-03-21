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


#include <Wire.h>            // Used to establish serial communication on the I2C bus
#include <SparkFun_TMP117.h> // Used to send and recieve specific information from our sensor

// The default address of the device is 0x48 = (GND)
TMP117 sensor; // Initalize sensor

void setup()
{
  Wire.begin();
  Serial.begin(115200);    // Start serial communication at 115200 baud
  Wire.setClock(400000);   // Set clock speed to be the fastest for better communication (fast mode)

  Serial.println("TMP117 Example 1: Basic Readings");
  if (sensor.begin() == true) // Function to check if the sensor will correctly self-identify with the proper Device ID/Address
  {
    Serial.println("Begin");
  }
  else
  {
    Serial.println("Device failed to setup- Freezing code.");
    while (1); // Runs forever
  }
}

void loop()
{
  // Data Ready is a flag for the conversion modes - in continous conversion the dataReady flag should always be high
  if (sensor.dataReady() == true) // Function to make sure that there is data ready to be printed, only prints temperature values when data is ready
  {
    float tempC = sensor.readTempC();
    float tempF = sensor.readTempF();
    // Print temperature in °C and °F
    Serial.println(); // Create a white space for easier viewing
    Serial.print("Temperature in Celsius: ");
    Serial.println(tempC);
    Serial.print("Temperature in Fahrenheit: ");
    Serial.println(tempF);
    delay(500); // Delay added for easier readings
  }
}
