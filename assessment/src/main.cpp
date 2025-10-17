
#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include "arduino_secrets.h"
// #include <ESPAsyncWebServer.h>

const char SSID[] = SECRET_SSID; //the secrets "tab" allows me to easily store different networks under comments sothat i can easily and qiuickly sub the different networks in depending on my location
const char PASSWORD[] = SECRET_PASS;

WiFiServer server(80);

const byte MEATPIN = 13;   //my meatpin (thermocouples)
const byte SENSORPIN = A5; //pin connection

//*WiFi stuff

void initWiFi() //setting up the wifi
{

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  Serial.print('Connecting to WiFi ..'); //displays in my serial monitor
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

  pinMode(MEATPIN, OUTPUT);
  pinMode(SENSORPIN, INPUT); // can have room and meat temps

  Serial.begin(115200);
  delay(5000);

  initWiFi();

  server.begin();
}

/************
 * loop stuff
 ************/
//under this section we are looping the output of the serial monitor displaying the IP for the website and whenever there is a new client it pauses and states so under the serial monitor aswell
void loop()
{

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

        /////////////////////////////
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

            // website displays from here
            //------------------------------------------------------------------------------
//below is the start to the webpage stating that ist in html, and then further goes on to clasify fonts and background colours
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");                                                                                                                  // from this to next /html its the webpage
            client.println("<style>html{font-family: Arial; background-color: white;}");   //background colour is white and standard font will be Arial                                                       
            client.println("<style>html{font-family: Arial; background-color: white;}table, th, td{border: 1px solid; boareder-collapse: collapse;}"); // only cplour if theres a
            client.println("</style>");
            client.println("<h1>The Meat Stick<h1>");    // Heading of the web page
            client.println("<h2>The Temperature </h2>"); // h2 to make the headingh smaller
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
            client.println("<button id='set-btn'>Set</button>");
            client.println("<button id='close-btn'>Close</button>");
            client.println("</div>");

            client.println(R"rawliteral(
<script>
  const settings = document.getElementById('settings');
  const section = document.getElementById('temperature-section');
  const closeBtn = document.getElementById('close-btn');
  const setBtn = document.getElementById('set-btn');
  const presetInput = document.getElementById('preset');
  const currentTemp = document.getElementById('current-temp');

  // Load saved temperature (if exists)
  const savedTemp = localStorage.getItem('presetTemp');
  if (savedTemp !== null) {
    currentTemp.innerHTML = savedTemp + '°C';
  } else {
    currentTemp.innerHTML = '24°C'; // default starting value
  }

  // Show the settings panel (manual close only)
  settings.onclick = function() {
    section.style.display = 'block';
    settings.innerHTML = 'Settings Page:';
  }

  // Close button hides the section
  closeBtn.onclick = function() {
    section.style.display = 'none';
    settings.innerHTML = 'Settings';
  }

  // When user sets a new preset
  setBtn.onclick = function() {
    const newTemp = parseInt(presetInput.value);
    if (isNaN(newTemp)) {
      alert('Please enter a valid temperature between 0 and 100°C.');
      return;
    }
    if (newTemp < 0 || newTemp > 100) {
      alert('Temperature must be between 0 and 100°C.');
      return;
    }

    // Save and display the new temperature
    currentTemp.innerHTML = newTemp + '°C';
    localStorage.setItem('presetTemp', newTemp);
    alert('Preset temperature set to ' + newTemp + '°C');
  }
</script>
)rawliteral");

            client.println("</body>");
            client.println("</html>");

            //------------------------------------------------------------------------------

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
