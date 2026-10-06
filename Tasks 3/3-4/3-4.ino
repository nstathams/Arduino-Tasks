const int LED_PINS[] = {3, 4, 5, 6, 7, 8};
const int LED_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

const int SWITCH = 2;
const unsigned long DEBOUNCE_TIME = 50;
const int STEP_TIME = 80;

int currentEffect = 0;
bool currentState = HIGH, lastState = HIGH, stableState = HIGH;
unsigned long lastChange = 0;

void setup() {
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  pinMode(SWITCH, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("effect 0");
}

void allOff() {
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
}

void effectRun() {
  for (int i = 0; i < LED_COUNT; i++) {
    allOff();
    digitalWrite(LED_PINS[i], HIGH);
    delay(STEP_TIME);
  }
}

void effectCount() {
  for (int i = 0; i < LED_COUNT / 2; i++) {
    allOff();
    digitalWrite(LED_PINS[i], HIGH);
    digitalWrite(LED_PINS[LED_COUNT - 1 - i], HIGH);
    delay(STEP_TIME);
  }
  allOff();
  delay(STEP_TIME);
}

void effectFill() {
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(STEP_TIME);
  }
  for (int i = 0; i < LED_COUNT; i++) {
    digitalWrite(LED_PINS[i], LOW);
    delay(STEP_TIME);
  }
}

void effectRandom() {
  allOff();
  digitalWrite(LED_PINS[random(LED_COUNT)], HIGH);
  delay(STEP_TIME);
}

void loop() {
  unsigned long currentTime = millis();

  bool newState = digitalRead(SWITCH);
  if (newState != lastState) {
    lastChange = currentTime;
  }

  if (currentTime - lastChange > DEBOUNCE_TIME && newState != stableState) {
    stableState = newState;
    if (stableState == LOW) {
      currentEffect = (currentEffect + 1) % 4;
      allOff();
      Serial.print("effect ");
      Serial.println(currentEffect);
    }
  }
  lastState = newState;

  switch (currentEffect) {
    case 0: effectRun(); break;
    case 1: effectCount(); break;
    case 2: effectFill(); break;
    case 3: effectRandom(); break;
  }
}
