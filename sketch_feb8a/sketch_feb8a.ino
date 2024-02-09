#include <Servo.h>

const byte ledPin = 13;
const byte PAW1 = 1;  //NZQA like constants
const byte PAW2 = 2;
const byte PAW3 = 3;
const byte PAW4 = 4;
const byte LEFTEARPIN = 9;  //constant must be in caps
const byte RIGHTEARPIN = 10;

Servo leftEar;
Servo rightEar;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(PAW1, INPUT);
  pinMode(PAW2, INPUT);
  pinMode(PAW3, INPUT);
  pinMode(PAW4, INPUT);
  leftEar.attach(LEFTEARPIN);
  rightEar.attach(RIGHTEARPIN);
}

void loop() {
  if (digitalRead(PAW1) == HIGH) {
    digitalWrite(ledPin, HIGH);
  }
  if (digitalRead(PAW2) == HIGH) {
    digitalWrite(ledPin, HIGH);
  }
  if (digitalRead(PAW3) == HIGH) {
    playMusic();
  }
  if (digitalRead(PAW4) == HIGH) {
    int score = playGame();
  }
  int playGame() {
    byte score = 99;
    //simon says game
    return sciore;
  }
}

void wagEars(){
  leftear.write(0);
  rightEar.write(0);
  leftEar.write(90);
  rightEar.write(90);
  leftEar.write(0);
  rightEar.write(0);
}

void blinkingLed(){
  byte randNumber = random(1,3);

  for (int i = 0; i < randNumber; i++){}
  digitalWrite(LEDPIN, HIGH);
  delay(500);
  digitalWrite(LEDPIN, LOW);
  delay(500);
}
}