
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
