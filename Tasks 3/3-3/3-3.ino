const int LED1 = 10, LED2 = 9, BUTTON = 2;
const unsigned long SHORT_MAX = 500, LONG_MIN = 1000, LED2_HOLD = 3000, DEBOUNCE = 50;

bool raw = HIGH, last = HIGH, stable = HIGH, led1 = false, led2On = false;
unsigned long changeTime = 0, pressTime = 0, led2Off = 0;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  
  unsigned long now = millis();
  raw = digitalRead(BUTTON);

  if (raw != last) changeTime = now;

  if (now - changeTime > DEBOUNCE && raw != stable) {
    stable = raw;
    if (stable == LOW){
      pressTime = now;
    } else {
      unsigned long held = now - pressTime;
      
      if (held < SHORT_MAX) {
        
        digitalWrite(LED1, led1 = !led1);
        Serial.print("SHORT LED1="); Serial.println(led1);
        
      } else if (held > LONG_MIN) {
        
        led2On = true; led2Off = now + LED2_HOLD;
        digitalWrite(LED2, HIGH);
        Serial.println("LONG LED2 ON");
        
      }
    }
  }
  
  last = raw;

  if (led2On && now >= led2Off) {
    digitalWrite(LED2, LOW);
    led2On = false;
    Serial.println("LED2 OFF");
  }
}
