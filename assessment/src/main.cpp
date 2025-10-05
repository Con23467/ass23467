#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include "arduino_secrets.h"
//#include <ESPAsyncWebServer.h>



const char SSID[] = SECRET_SSID; //change
const char PASSWORD[] = SECRET_PASS;

WiFiServer server(80);

const byte MEATPIN = 13;
const byte SENSORPIN = A5;

//*WiFi stuff

void initWiFi()
{
  
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    Serial.print('Connecting to WiFi ..');
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print('.');
        delay(1000);
    }
    delay(5000);
Serial.print("Connected to ");
Serial.println(SSID);

Serial.print("Use http://");
Serial.println(WiFi.localIP());
}

/************
 * Setup stuff
 ************/
void setup()
{

  pinMode(MEATPIN, OUTPUT);
  pinMode(SENSORPIN, INPUT); //can have room and meat temps

  Serial.begin(115200);
  delay(5000); 

  initWiFi();

  server.begin();
}

/************
 * loop stuff
 ************/
void loop()
{

Serial.print("Use http://");
Serial.println(WiFi.localIP());
  //check if anyone connects to the ESP32
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("new client");
    //variable to hold any incoming data from the browser or client
    String currentLine = "";

    //while they are connected
    while (client.connected()) //check if server is avaliable/client has connected
    {
      if (client.available())//while connected
      {
        //another variable to hold any incoming
        char c = client.read();
        Serial.write(c);

        /////////////////////////////
        //if browser sent a newline character
        if (c == '\n')
        {
          //if the current line is blank, you
          //that's the end of the client HTTP
          if (currentLine.length() == 0)
          {
            //HTTP code for a webpage after some initial set
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println("Connection: close");
            client.println("Refresh: 5"); //refresh
            client.println();

             //HAN REORDERED ----------------------------------
        if(currentLine.endsWith("GET /H"))
        {
          digitalWrite(MEATPIN, HIGH); // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L"))
        {
          digitalWrite(MEATPIN, LOW); // GET /L turns the LED off
        }
         if (currentLine.endsWith("GET /set"))
       //Settings page under here
         {
           //HAN ADDED ----------------------------------
        pasteSettingspage();
        }
        //Settings page ends here

//HAN ADDED ----------------------------------
          if (currentLine.endsWith("GET /main"))  
 pasteHomepage();
           
          }
//HAN - not sure how to get it to default to main on first visit, maybe this
          //or maybe just an if statement around line 94 with a boolean set to true for first time
          //then false after that time by toggling it to false
currentLine += "/main\"; //add main to the end of the current line
            
            break; //leave the while loop
            }
            else
            {// if you got a first newline, then clear currentLine variable 
              currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c; //add c to the end of the current line
        }
        




      } //end of the client.avaliable
    }//end of while loop
    //close the connection at the ESP32 end as 
    //the client is not connected (see while loop above)
    client.stop();
    Serial.println("client disconnected");
  }//end of if client
}

//HAN ADDED ----------------------------------
void pasteHomepage(){
 client.println("<!DOCTYPE HTML>");
            client.println("<html>"); //from this to next /html its the webpage
            client.println("<style>html{font-family: Arial; background-color: white;}table, th, td{border: 1px solid; boareder-collapse: collapse;}");//only cplour if theres a 
            client.println("</style>");
            client.println("<h1>The Meat Stick</h1>"); //Heading
            client.print(" <a href=\"/set\">Settings</a><br>"); //the slash h creates the hyperlink, make descrioptive
            //client.print("Click <a href=\"/L\">here</a> turn the LED off<br>");
            client.println("<h1>The Temperature </h1>");
            client.println("<h1>Connor's Meat Guide</h1>");


            int sensorReading = analogRead(SENSORPIN);
            //client.print("Temperature is: <tr> "); //use output the value of an analog input pin
            client.print(sensorReading);
            
          
           //client.println("<h1>Connor's Meat Guide<h1>");

           client.println("<table>");
           client.println("<tr>");
           client.println("<th>Steak Type</th>");
           client.println("<th>Colour</th>");   
           client.println("<th>Temperature (Degrees C)</th>"); 
           client.println("</tr>"); 
           client.println("<tr>"); 
           client.println("<td>Rare</td>"); 
           client.println("<td>Blood Red</td>");
           client.println("<td>50</td>");
           client.println("</tr>");
           client.println("<tr>");

           client.println("<td>Medium Rare</td>");
           client.println("<td>Pink</td>");
           client.println("<td>54-57</td>");
           client.println("</tr>");
           client.println("<tr>");
          
           client.println("<td>Medium</td>");
           client.println("<td>Pinky Brown</td>");
           client.println("<td>58-62</td>");
           client.println("</tr>");
           client.println("<tr>");

           client.println("<td>Medium Well</td>");
           client.println("<td>Light Brown</td>");
           client.println("<td>63-68</td>");
           client.println("</tr>");
           client.println("tr>"); 

           client.println("<td>Well</td>");
           client.println("<td>Brown</td>");
           client.println("<td>69</td>");
           client.println("</tr>");
           client.println("<tr>");
           client.println("</table>"); 
           client.println("</html>");  //end of displayed webpage
           
          
      
            //output different text depending on the LED value
            //byte MEATReading = digitalRead(MEATPIN);
            //if(MEATReading == HIGH){
             // client.print("Red LED is on<br><br>"); //br is the line break
           // }else{
             // client.print("Red LED is off<br><br>");
           // }
            //when  you click either of these links you add a H or L into the
            //and that gets read by if statements below
            //below create the hyper links
            
            //below is example
            //client.print("Click <a href=\"/H\">Settings</a> turn the LED on<br>"); //the slash h creates the hyperlink, make descrioptive
            //client.print("Click <a href=\"/L\">here</a> turn the LED off<br>"); 

<<<<<<< HEAD
            
            break; //leave the while loop
            }
            else
            {// if you got a first newline, then clear currentLine variable }
              currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c; //add to the end of the current line
        }
        if(currentLine.endsWith("GET /H"))
        {
          digitalWrite(MEATPIN, HIGH); // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L"))
        {
          digitalWrite(MEATPIN, LOW); // GET /L turns the LED off
        }
         if (currentLine.endsWith("GET /set"))
       //Settings page under here
         {
         client.println("<!DOCTYPE HTML>");
=======
            client.println("</html>");
}

//HAN ADDED ----------------------------------
void pasteSettingspage(){
client.println("<!DOCTYPE HTML>");
>>>>>>> 5765c4d970d2d66bd74888d9c95318477c736b19
            client.println("<html>"); //from this to next /html its the webpage
            client.println("<style>html{font-family: Arial; background-color: lightblue;}");//only cplour if theres a 
            client.println("</style>");
            client.println("<h1>Settings page</h1>"); //Heading
            client.print(" <a href=\"/main\">Homepage</a><br>"); //the slash h creates the hyperlink, make descrioptive
            client.println("<h1>Set Temperature</h1>");
<<<<<<< HEAD
            client.println("</html>");  //end of displayed webpage
        }
        //Settings page ends here



      } //end of the client.avaliable
    }//end of while loop
    //close the connection at the ESP32 end as 
    //the client is not connected (see while loop above)
    client.stop();
    Serial.println("client disconnected");
  }//end of if client
=======
>>>>>>> 5765c4d970d2d66bd74888d9c95318477c736b19
}
