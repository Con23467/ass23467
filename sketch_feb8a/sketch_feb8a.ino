#include <Servo.h>

const byte ledPin = 13;       //setting up LED to pin 13  //NZQA like constants
const byte PAW1 = 1;          //setting up top right paw to pin 4
const byte PAW2 = 2;          //setting up the top left paw to pin 2
const byte PAW3 = 3;          //setting up the bottom left paw to pin 3
const byte PAW4 = 4;          //setting up the bottom right paw to pin 4
const byte LEFTEARPIN = 9;    //constant must be in caps
const byte RIGHTEARPIN = 10;  //setting up the constant variable of the rightear pin to pin 10

Servo leftEar;   //setting up the leftear servo
Servo rightEar;  // setting up the rightear servo

//setting up the pins as either inputs or outputs
void setup() {
  pinMode(ledPin, OUTPUT);  //saying that the led will be outputting light
  pinMode(PAW1, INPUT);
  pinMode(PAW2, INPUT);
  pinMode(PAW3, INPUT);
  pinMode(PAW4, INPUT);
  leftEar.attach(LEFTEARPIN);
  rightEar.attach(RIGHTEARPIN);
}

void loop() {
  //if we press paw 1 then the led turns on
  if (digitalRead(PAWPIN1) == HIGH) {
    digitalWrite(LEDPIN, HIGH);
  }
  //when we press paw 2 it switches off the led
  if (digitalRead(PAWPIN2) == HIGH) {
    digitalWrite(LEDPIN, LOW);
  }
  //If paw 3 is pressed then call then do the wag ears method
  if (digitalRead(PAWPIN3) == HIGH) {
    wagEars();
  }
  //If paw 4 is pressed then call blinkingLed method
  if (digitalRead(PAWPIN4) == HIGH) {
    blibkingLed();
  }
}

//move both ears to 0 then 90 then back to 0 degrees
void wagEars() {
  leftear.write(0);
  rightEar.write(0);
  leftEar.write(90);
  rightEar.write(90);
  leftEar.write(0);
  rightEar.write(0);
}

}
int playGame() {
  byte score = 99;
  //simon says game
  return sciore;
}
}



void blinkingLed() {
  byte randNumber = random(1, 3);

  for (int i = 0; i < randNumber; i++) {}
  digitalWrite(LEDPIN, HIGH);
  delay(500);
  digitalWrite(LEDPIN, LOW);
  delay(500);
}
}