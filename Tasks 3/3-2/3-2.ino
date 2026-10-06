const int LED = 9;
const int BUTTON = 2;

bool ledState = false;

bool currentReading = HIGH;
bool lastReading = HIGH;
bool stableState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_MS = 50;

unsigned int pressCount = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  currentReading = digitalRead(BUTTON);

  if (currentReading != lastReading) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > DEBOUNCE_MS) {
    if (currentReading != stableState) {
      stableState = currentReading;
      
      if (stableState == LOW) {
        ledState = !ledState;
        digitalWrite(LED, ledState);
        pressCount++;
        Serial.print("presses = ");
        Serial.println(pressCount);
      }
    }
  }

  lastReading = currentReading;
}
