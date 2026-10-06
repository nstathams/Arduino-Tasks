const int POT_PIN = A0;
const int LED_PIN = 8;

const unsigned long LOG_INTERVAL = 200;
unsigned long lastLog = 0;

const int LOW_DEADZONE = 1023 * 0.02;
const int HIGH_DEADZONE = 1023 - (1023 * 0.02);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int rawValue = analogRead(POT_PIN);
  int pwmValue;

  if (rawValue <= LOW_DEADZONE) {
    pwmValue = 0;
  } else if (rawValue >= HIGH_DEADZONE) {
    pwmValue = 255;
  } else {
    pwmValue = map(rawValue, LOW_DEADZONE, HIGH_DEADZONE, 1, 254);
    pwmValue = constrain(pwmValue, 0, 255);
  }

  analogWrite(LED_PIN, pwmValue);

  if (millis() - lastLog >= LOG_INTERVAL) {
    lastLog = millis();
    Serial.print("Raw: ");
    Serial.print(rawValue);
    Serial.print("\t");
    Serial.print("PWM: ");
    Serial.println(pwmValue);
  }
}
