//we are including the 3 libraries so that we can have the relevant functions implamented in our code
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>

//for the delay to adjust all at same tukme

LPS25HB sensor;                            //The LPS25HB is a pressure sensor wich functions as a digital output barometer
OpenLog SDcard;                            //Create instance/labeling the Log as SDcard
const String FILENAME = "rocketdata.txt";  //the FILENAME is being called/saved as rocketdata.txt

void setup() {         //Initializes the serial moniter/sets up the serial moniter
  Serial.begin(9600);  //This tells the arduino to get ready to connect to the serial monitor
  Wire.begin();        //initialises the wire library and joins the I2C bus as a controller.
  sensor.begin();      //"Makes" the sensor start reading its sourroundings
  SDcard.begin();      //Also makes/allows the SDcard to begin its function, sort of waking it up from a long sleep and telling it to start working
  delay(1000);         //Delaying the next statement by 1 second, allowing everything above to be fully complete before progressing further with the instructions

  if (sensor.isConnected() == false) {           //we are setting up the if statement, so if something happens then the task in the {} will happen
    Serial.println("Sensor hasn't been read.");  //Serial printing that the sensor has not been read yet allowing me to figure out a. if the code was working up to this point and b. seeing if the code hasn't been read yet so that I know if the connection isn't correct or if there is a fault somewhere in the sensor
    while (1)
      ;
  }

  byte status = SDcard.getStatus();
  if (status == 0xFF)
  {
    Serial.println("SDcard failed to respond.");
    while (1) //(pause)
      ;
  }

  SDcard.append(FILENAME);
  SDcard.println("Pressure, Temperature");
  SDcard.syncFile();
}

void loop() {     //the void loop is being used to loop (repeat) the code in the loop ({}) with the serial monitor printing out the pressure and temperature values. The loop is bing used to repeatedly remeausre the values.
  launch(false);  // t=debug f=launch
  delay(4000);    //every 40 milliseconds the task repeats itself, giving us new values.
}

void launch(bool debug) { //This is setting up my method for the launch sequence
  if (debug == true) { //we are saying that when our debug is true our serial monitor will output the text that is hardcoded and then the temperature and pressure which is dependent on everything outside the rockets control 

    Serial.print("Current Pressure is: ");         //The serial print is printing out "Current Pressure is:" and then the following line will be outputting the current pressure
    Serial.println(sensor.getPressure_hPa());      //The serial println is is showing us the pressure values on the serial monitor, showing us what is being inputted to the sensor
    Serial.print("Current Temperature (°C)");      //The serial print is showing us the temperature values on the serial monitor, showing us what is being inputted
    Serial.println(sensor.getTemperature_degC());  //The serial print is showing us the temperature values on the serial monitor, showing us what is being inputted

  } else {

    //the SDcard print and println is writing out the values for the pressure and the temperature then saving it to the SD card. The same things are happening in the next for lines as in the top four lines of code
    // SDcard.print("Current pressure: ");
    SDcard.print(sensor.getPressure_hPa());
    SDcard.print(",");
    SDcard.println(sensor.getTemperature_degC());  // the SDcard is saving the values to the SD card

    SDcard.syncFile();
  }
}