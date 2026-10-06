const int LED_PIN = 8;
const int SWITCH_PIN = 2;

bool useGammaCorrection = false;
int currentLevel = 0;
int stepValue = 5;

uint8_t applyGamma(uint8_t rawValue) {
  return (uint16_t)rawValue * rawValue / 255;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(SWITCH_PIN) == LOW) {
    useGammaCorrection = !useGammaCorrection;
    Serial.println(useGammaCorrection ? "gamma" : "linear");
    delay(300);
  }

  if (useGammaCorrection) {
    analogWrite(LED_PIN, applyGamma(currentLevel));
  } else {
    analogWrite(LED_PIN, currentLevel);
  }

  currentLevel += stepValue;
  if (currentLevel <= 0 || currentLevel >= 255) {
    stepValue = -stepValue;
  }

  delay(30);
}
