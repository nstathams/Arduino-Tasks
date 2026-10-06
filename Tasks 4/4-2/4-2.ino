const int RED = 11, GREEN = 10, BLUE = 9;

void setColor(uint8_t r, uint8_t g, uint8_t b) {
    analogWrite(RED, r);
    analogWrite(GREEN, g);
    analogWrite(BLUE, b);
}

void setup() {
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
}

void loop() {
    for (int v = 128; v <= 255; v++) {
      setColor(v, 0, 0);
      delay(5);
    }
    for (int v = 0; v <= 255; v++) {
       setColor(255, v, 0);
      delay(5);
    }
    for (int v = 255; v >= 0; v--) {
       setColor(v, 255, 0);
      delay(5);
    }
    for (int v = 0; v <= 255; v++) {
       setColor(0, 255, v);
      delay(6);
    }
    for (int v = 255; v >= 0; v--) {
       setColor(0, v, 255);
      delay(5);
    }
    for (int v = 0; v <= 128; v++ ) {
       setColor(v, 0, 255);
      delay(5);
    }
    for (int v = 255; v >= 0; v--) {
       setColor(128, 0, v);
      delay(5);
    }
}
