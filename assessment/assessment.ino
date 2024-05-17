//we are including the 3 libraries so that we can have the relevant functions implamented in our code
#include <SparkFun_LPS25HB_Arduino_Library.h>
#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>

LPS25HB sensor;                            //The LPS25HB is a pressure sensor wich functions as a digital output barometer
OpenLog SDcard;                            //Create instance/labeling the Log as SDcard
const String FILENAME = "rocketdata.txt";  //the FILENAME is being called/saved as rocketdata.txt
const int MYDELAY = 500;                   //setting up MYDELAY as a constant integer of 0.5 seconds (The time span can be changed)


void setup() {         //Initializes the serial moniter/sets up the serial moniter
  Serial.begin(9600);  //This tells the arduino to get ready to connect to the serial monitor
  Wire.begin();        //initialises the wire library and joins the I2C bus as a controller.
  sensor.begin();      //"Makes" the sensor start reading its sourroundings
  SDcard.begin();      //Also makes/allows the SDcard to begin its function, sort of waking it up from a long sleep and telling it to start working
  delay(MYDELAY);      //Delaying the next statement by the set amount of seconds, allowing everything above to be fully complete before progressing further with the instructions

  if (sensor.isConnected() == false) {           //we are setting up the if statement, so if something happens then the task in the {} will happen
    Serial.println("Sensor hasn't been read.");  //Serial printing that the sensor has not been read yet allowing me to figure out a. if the code was working up to this point and b. seeing if the code hasn't been read yet so that I know if the connection isn't correct or if there is a fault somewhere in the sensor
    while (1)                                    //code pauses/freezes for a second
      ;
  }

  byte status = SDcard.getStatus();               //get the status from SDcard and give it to the varible status
  if (status == 0xFF) {                           //if the status meets a ceratin criteria then (Continue next line)
    Serial.println("SDcard failed to respond.");  //Serial monitor is outputting "SDcard failed to respond." allowing me to know whether the SDcard is responsive and working or not, if it skips this messaqge It likely is working as shown by the following messages
    while (1)                                     //(pause)
      ;
  }

  if (status & 1 << STATUS_SD_INIT_GOOD) {   //If the Status meets this criteria then (Proceed with next 3 lines of code)
    Serial.println("SDcard is responsive");  //Serial moitor is telling me that the SDcard is being recognized/read and working
  } else {
    Serial.println("Is the SDcard present?");  //Serial monitor outputs "Is the SDcard present?"
  }

  SDcard.append(FILENAME);                  //the FILENAME (rocketdata.txt) is what the SDcards file will be saved as
  SDcard.println("Pressure, Temperature");  //The headings, Pressure and Temperature will be at the top of the file and then the values will be outputted below them
  SDcard.syncFile();                        //syncing the file to save the information onto ("rocketdata")
  Serial.println("setup done");             //This was done for testing purposes to ensure that this piece of code was being acted on and working
}

void loop() {      //the void loop is being used to loop (repeat) the code in the loop ({}) with the serial monitor printing out the pressure and temperature values. The loop is bing used to repeatedly remeausre the values.
  launch(true);    // t=debug f=launch //add this to testing if they're true and false
  delay(MYDELAY);  //every 0.5 seconds (As set) so the task repeats itself, giving us new values. This can be changed when the final time incroments are deceided.
}

void launch(bool debug) {  //This is setting up my method for the launch sequence
  if (debug == true) {     //we are saying that when our debug is true our serial monitor will output the text that is set and then the temperature and pressure which is dependent on everything outside the rockets control

    Serial.print("Current Pressure is: ");         //The serial print is printing out "Current Pressure is:" and then the following line will be outputting the current pressure
    Serial.println(sensor.getPressure_hPa());      //The serial println is is showing us the pressure values on the serial monitor, showing us what is being inputted to the sensor
    Serial.print("Current Temperature (°C):");     //The serial print is printing out "Current Temperature (°C):" and then the following line will be outputting the current temperature
    Serial.println(sensor.getTemperature_degC());  //The serial print is showing us the temperature values on the serial monitor, showing us what is being inputted

  } else {  //if false then do this

    //the SDcard print and println is writing out the values for the pressure and the temperature then saving it to the SD card. The same things are happening in the next for lines as in the top four lines of code
    // SDcard.print("Current pressure: ");
    SDcard.print(sensor.getPressure_hPa());
    SDcard.print(",");                             //a comma is being printed between the two values, sepertaing them and enforcing  the CSV format
    SDcard.println(sensor.getTemperature_degC());  // the SDcard is saving the values to the SD card

    SDcard.syncFile();  //syncing the information to the file "rocketdata.txt" sothat it is accessable and findable when I plug the SDcard into my laptop
  }
}