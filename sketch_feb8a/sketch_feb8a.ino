const byte ledPin = 13;

const byte PAW1 = 1;  //NZQA like constants
const byte PAW2 = 2;
const byte PAW3 = 3;
const byte PAW4 = 4;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(PAW1, INPUT);
  pinMode(PAW2, INPUT);
  pinMode(PAW3, INPUT);
  pinMode(PAW4, INPUT);
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
}