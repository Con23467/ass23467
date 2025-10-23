#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include <arduino_secrets.h>
#include <max6675.h>
#include <Adafruit_ST7789.h>
// #include <ESPAsyncWebServer.h>

const char SSID[] = SECRET_SSID; //the secrets "tab" allows me to easily store different networks under comments sothat i can easily and qiuickly sub the different networks in depending on my location
const char PASSWORD[] = SECRET_PASS;

//HAN Notes - What does this do?
WiFiServer server(80);

const byte MEATPIN = 13;   //my meatpin (thermocouples)
const byte SENSORPIN = A5; //pin connection


int thermoDO = GPIO_NUM_37;
int thermoCS = GPIO_NUM_35;
int thermoCLK = 6;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

Adafruit_ST7789 screen = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST); //library //screen working 

/************
 * WiFi stuff
 ************/
void initWiFi()
{
//HAN Notes - What does this do?
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.print('Connecting to WiFi ..'); //displays in my serial monitor

  //HAN Notes - What does this do?
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  delay(5000);
  Serial.print("Connected to "); //if it connects displays this then moves to printing the SSID after this phrase further progressing to use http://
  Serial.println(SSID);

  Serial.print("Use http://"); //when here it outputs the website ip (the http:// outputs first then the linebelow does the number sequence)
  Serial.println(WiFi.localIP()); 
}

/************
 * Setup stuff
 ************/
//under this section its all the boring setup parts, the thermocoiuples being asigned as inputs and buzzer as output
void setup()
{
  
  Serial.begin(115200);

pinMode(TFT_BACKLITE, OUTPUT);
  digitalWrite(TFT_BACKLITE, HIGH);

  // turn on the screen / I2C power supply
  pinMode(TFT_I2C_POWER, OUTPUT);
  digitalWrite(TFT_I2C_POWER, HIGH);
  delay(10);

  // initialize screen
  screen.init(135, 240); // Init ST7789 240x135
  screen.setRotation(3);
  screen.fillScreen(ST77XX_YELLOW); 

  Serial.println(F("screen is on"));



  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);

  /*
  //HAN Notes - What does this do?
  pinMode(MEATPIN, OUTPUT);
  pinMode(SENSORPIN, INPUT); // can have room and meat temps

  Serial.begin(115200);
  delay(5000);
*/
  //HAN notes - What does this do?
  initWiFi();
  
  //HAN Notes - What does this do?
  server.begin();
}

/************
 * loop stuff
 ************/
//under this section we are looping the output of the serial monitor displaying the IP for the website and whenever there is a new client it pauses and states so under the serial monitor aswell
void loop()
{
  /* 
screen.setCursor(0, 0);
  screen.setTextColor(ST77XX_BLACK);
  screen.setTextSize(2);
  screen.setTextWrap(true);
  //displays the temperature on the screen
  screen.print(F("C = "));
  screen.print(thermocouple.readCelsius());
*/

  // basic readout test, just print the current temp
 
  Serial.print("C = ");
  Serial.println(thermocouple.readCelsius());
  Serial.print("F = ");
  Serial.println(thermocouple.readFahrenheit());
 
  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(1000);


  Serial.print("Use http://");
  Serial.println(WiFi.localIP());
  // check if anyone connects to the ESP32
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("new client");
    // variable to hold any incoming data from the browser or client
    String currentLine = "";

    // while they are connected
    while (client.connected()) // check if server is avaliable/client has connected
    {
      if (client.available()) // while connected
      {
        // another variable to hold any incoming
        char c = client.read();
        Serial.write(c);
        // if browser sent a newline character
        if (c == '\n')
        {
          // if the current line is blank, you
          // that's the end of the client HTTP
          if (currentLine.length() == 0)
          {
            // HTTP code for a webpage after some initial set
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println("Refresh: 30"); // refresh and include in testing 5 was too quick but lonegr like a minute is morte than necesery
            client.println();


//below is the start to the webpage stating that ist in html, and then further goes on to clasify fonts and background colours
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");                                                                                                                  // from this to next /html its the webpage
            client.println("<style>html{font-family: Arial; background-color: white;}");   //background colour is white and standard font will be Arial                                                       
            client.println("<style>html{font-family: Arial; background-color: white;}table, th, td{border: 1px solid; boareder-collapse: collapse;}"); // only cplour if theres a
            client.println("</style>");
            client.println("<h1>The Meat Stick<h1>");    // Heading of the web page
            client.println("<h2>The Temperature is 92 Degrees Celcius </h2>"); // h2 to make the headingh smaller
            client.println("<h2 style=\"font-family: 'Great Vibes', cursive; font-size: 36px; color: #513ccc; font-style: italic;\">Connor's Meat Guide</h2>"); //this line is giving the heading "Connors Meat Guide" its font, italics and colour (Royal Blue)

            int sensorReading = analogRead(SENSORPIN);
            // client.print("Temperature is: <tr> "); //use output the value of an analog input pin
            client.print(sensorReading);

            //below is my table of meat types. Under each section it displays the Type of cook (under heading Steak Type), then under Colour - the different colours and lastly the ideal temperatures under Temperature (degrees C)
            client.println("<table>"); //startys the table/opens the command for the table
            client.println("<tr>");
            client.println("<th>Steak Type</th>");
            client.println("<th>Colour</th>");
            client.println("<th>Temperature (Degrees C)</th>");
            client.println("</tr>");
            client.println("<tr>");
            client.println("<td>Rare</td>");
            client.println("<td style='color:darkred;'>Blood Red</td>");
            client.println("<td>50</td>");
            client.println("</tr>");
            client.println("<tr>");

            client.println("<td>Medium Rare</td>");
            client.println("<td style='color:deeppink;'>Pink</td>");
            client.println("<td>54-57</td>");
            client.println("</tr>");
            client.println("<tr>");

            client.println("<td>Medium</td>");
            client.println("<td style='color:#C07050;'>Pinky Brown</td>");
            client.println("<td>58-62</td>");
            client.println("</tr>");
            client.println("<tr>");

            client.println("<td>Medium Well</td>");
            client.println("<td style='color:peru;'>Light Brown</td>");
            client.println("<td>63-68</td>");
            client.println("</tr>");
            client.println("tr>");

            client.println("<td>Well</td>");
            client.println("<td style='color:brown;'>Brown</td>");
            client.println("<td>69</td>");
            client.println("</tr>");
            client.println("<tr>");
            client.println("</table>"); // the ("</table>") closes the table/ ends the table. Any info added now won't be added into the table
          
            //this section is before my settings page - giving basic text after the table and then assigning the Settings phrase on the website to be the signal to continue with the settings page drop down once clicked
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<body>");
            client.println("<br>");
            client.println("To change setting, click the Settings text drop down below:");
            client.println("<h2 id='settings'>Settings</h2>");

            //this section holds all the information and background work shown (and not shown) for the settings page
            client.println("<div id='temperature-section' style='display:none; border:1px solid black; padding:10px; width:250px; margin-top:10px;'>"); //creating the box around the settings page
            client.println("<p>Preset Temperature: <span id='current-temp'>--°C</span></p>"); //Allowing the temperature to be preset 
            client.println("<label for='preset'>Set Preset Temperature:</label><br>");
            client.println("<input type='number' id='preset' min='0' max='100' placeholder='Enter °C'><br><br>"); //making the max and min range for temperature settings from 0 - 11
            client.println("<button id='set-btn'>Set</button>");//this is the set button command - once clicked the users preset te,perature will now be stored under the settings display
            client.println("<button id='close-btn'>Close</button>");//this is the close button on the settings page, once clicked the settings page disappears
            client.println("</div>");

  //HAN Notes - What does this do?
            client.println(R"rawliteral(
<script>
//in this section we are getting references to HTML elements from their Ids
  const settings = document.getElementById('settings');
  const section = document.getElementById('temperature-section');
  const closeBtn = document.getElementById('close-btn');
  const setBtn = document.getElementById('set-btn');
  const presetInput = document.getElementById('preset');
  const currentTemp = document.getElementById('current-temp');

  // Load saved PRESET temperature from the localStorage (if one has been put in)
  const savedTemp = localStorage.getItem('presetTemp');
  //If a savedTemp = localStorage.getItem('presetTemp');
  if (savedTemp !== null) {
  //If a saved temperature exists, show it on the page
    currentTemp.innerHTML = savedTemp + '°C';
  } else {
   //defult to 24°C
    currentTemp.innerHTML = '24°C'; // default starting value
  }

  // show the settings pannel when the user clicks "Settings" ---
  settings.onclick = function() {
    section.style.display = 'block'; //makes temperature section avaliable
    settings.innerHTML = 'Settings Page:'; //chnages button text to indicate active state
  }

  // Close button hides the section when the user clicks "Close"
  closeBtn.onclick = function() {
    section.style.display = 'none'; //hides the settings section again
    settings.innerHTML = 'Settings'; //resets button text
  }

  // When user sets a new preset
  setBtn.onclick = function() {
    const newTemp = parseInt(presetInput.value); //convert input string into integer
    //valadation: ensure input is a number
    if (isNaN(newTemp)) {
      alert('Please enter a valid temperature between 0 and 100°C.');
      return;
    }
      //valadation: ensure the temp is within realistic range
    if (newTemp < 0 || newTemp > 100) {
      alert('Temperature must be between 0 and 100°C.');
      return;
    }

    // Save and display the new temperature (only valid temps)
    currentTemp.innerHTML = newTemp + '°C';
    localStorage.setItem('presetTemp', newTemp);
    //Give the user feedback
    alert('Preset temperature set to ' + newTemp + '°C');
  }
</script>
)rawliteral");

            client.println("</body>");
            client.println("</html>");

            break; // leave the while loop
          }
          else
          { // if you got a first newline, then clear currentLine variable }
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c; // add to the end of the current line
        }
        if (currentLine.endsWith("GET /H"))
        {
          digitalWrite(MEATPIN, HIGH); // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L"))
        {
          digitalWrite(MEATPIN, LOW); // GET /L turns the LED off
        }
      } // end of the client.avaliable
    } // end of while loop
    // close the connection at the ESP32 end as
    // the client is not connected (see while loop above)
    client.stop();
    Serial.println("client disconnected");
  } // end of if client
}
