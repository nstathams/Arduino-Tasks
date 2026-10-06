const int pinCarRed     = 10;
const int pinCarYellow  = 9;
const int pinCarGreen   = 8;

const int pinPedRed     = 7;
const int pinPedGreen   = 6;
const int pinButton     = 2;

const int durationBlink      = 300;
const int durationYellow     = 2000;
const int durationPedGreen   = 5000;
const int durationDebounce   = 50;

bool isPedestrianCycleActive = false;

void setup() {
  pinMode(pinCarRed, OUTPUT);
  pinMode(pinCarYellow, OUTPUT);
  pinMode(pinCarGreen, OUTPUT);
  pinMode(pinPedRed, OUTPUT);
  pinMode(pinPedGreen, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  Serial.begin(9600);
  enterIdleState();
}

void enterIdleState() {
  digitalWrite(pinCarRed, LOW);
  digitalWrite(pinCarYellow, LOW);
  digitalWrite(pinCarGreen, HIGH);
  digitalWrite(pinPedRed, HIGH);
  digitalWrite(pinPedGreen, LOW);
  isPedestrianCycleActive = false;
}

void turnOffAllCarLights() {
  digitalWrite(pinCarRed, LOW);
  digitalWrite(pinCarYellow, LOW);
  digitalWrite(pinCarGreen, LOW);
}

void executePedestrianCycle() {
  isPedestrianCycleActive = true;
  Serial.println("Pedestrian request accepted");

  turnOffAllCarLights();
  digitalWrite(pinPedRed, HIGH);

  for (int i = 0; i < 3; i++) {
    digitalWrite(pinCarGreen, HIGH);
    delay(durationBlink);
    digitalWrite(pinCarGreen, LOW);
    delay(durationBlink);
  }

  digitalWrite(pinCarYellow, HIGH);
  delay(durationYellow);
  digitalWrite(pinCarYellow, LOW);

  digitalWrite(pinCarRed, HIGH);
  digitalWrite(pinPedRed, LOW);
  digitalWrite(pinPedGreen, HIGH);
  delay(durationPedGreen);

  for (int i = 0; i < 5; i++) {
    digitalWrite(pinPedGreen, HIGH);
    delay(durationBlink);
    digitalWrite(pinPedGreen, LOW);
    delay(durationBlink);
  }

  enterIdleState();
  Serial.println("Back to idle");
}

void loop() {
  if (!isPedestrianCycleActive && digitalRead(pinButton) == LOW) {
    delay(durationDebounce);
    if (digitalRead(pinButton) == LOW) {
      executePedestrianCycle();
      while (digitalRead(pinButton) == LOW) {
        delay(10);
      }
    }
  }
}
