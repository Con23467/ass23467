
#include <Wire.h>
#include <SparkFun_Qwiic_OpenLog_Arduino_Library.h>
OpenLog sdCard;  //Create instance

const String FILENAME = "joke.txt";

void setup() {
  Wire.begin();
  sdCard.begin();  //Open connection to OpenLog (no pun intended)
  Serial.begin(9600);

  sdCard.append(FILENAME);
  sdCard.println("Knock knock Joke");
  sdCard.syncFile();
}
void loop() {
  sdCard.println("Knock Kncok!");
  Serial.println("Knock Kncok!");

  sdCard.println("Who's there?");
  Serial.println("Who's there?");

  sdCard.println("Justin's grade.");
  Serial.println("Justin's grade.");

  sdCard.println("South African wimpering");
  Serial.println("South African wimpering");
}

