const int POT_PIN = A0;
const int PIN_RED = 8;
const int PIN_GREEN = 9;
const int PIN_BLUE = 10;

const int ZONE_GREEN_LIMIT = 341;    // 0..341   — зелёный
const int ZONE_YELLOW_LIMIT = 682;   // 341..682 — жёлтый
                                     // 682..1023 — красный

const int TRANSITION_WIDTH = 80;

const unsigned long LOG_INTERVAL = 200;
unsigned long lastLogTime = 0;

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  Serial.begin(9600);
}

int limitTo255(int value) {
  if (value < 0) return 0;
  if (value > 255) return 255;
  return value;
}

void loop() {
  int rawValue = analogRead(POT_PIN);

  int redVal = 0, greenVal = 0, blueVal = 0;

  if (rawValue < ZONE_GREEN_LIMIT - TRANSITION_WIDTH) {
    greenVal = 255;
  } 
  else if (rawValue < ZONE_GREEN_LIMIT + TRANSITION_WIDTH) {
    int blendFactor = map(rawValue, 
                          ZONE_GREEN_LIMIT - TRANSITION_WIDTH, 
                          ZONE_GREEN_LIMIT + TRANSITION_WIDTH, 
                          0, 255);
    greenVal = 255;
    redVal = blendFactor;
  } 
  else if (rawValue < ZONE_YELLOW_LIMIT - TRANSITION_WIDTH) {
    redVal = 255; 
    greenVal = 255;
  } 
  else if (rawValue < ZONE_YELLOW_LIMIT + TRANSITION_WIDTH) {
    int blendFactor = map(rawValue, 
                          ZONE_YELLOW_LIMIT - TRANSITION_WIDTH, 
                          ZONE_YELLOW_LIMIT + TRANSITION_WIDTH, 
                          0, 255);
    redVal = 255;
    greenVal = 255 - blendFactor;
  } 
  else {
    redVal = 255;
  }

  analogWrite(PIN_RED, limitTo255(redVal));
  analogWrite(PIN_GREEN, limitTo255(greenVal));
  analogWrite(PIN_BLUE, limitTo255(blueVal));

  if (millis() - lastLogTime >= LOG_INTERVAL) {
    lastLogTime = millis();
    Serial.print("Raw: ");
    Serial.print(rawValue);
    Serial.print(" R: ");  
    Serial.print(redVal);
    Serial.print(" G: ");   
    Serial.print(greenVal);
    Serial.print(" B: ");   
    Serial.println(blueVal);
  }
}
