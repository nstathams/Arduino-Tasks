#include <Servo.h>
Servo myservo;

const int PWM_PINS[] = {3, 5, 6, 9, 10, 11};
const int NUM_LEDS = 6;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(PWM_PINS[i], OUTPUT);
    analogWrite(PWM_PINS[i], 128);
  }
  delay(2000);

  // ЭТАП 1: добавляем tone(8, 440, 100) раз в секунду
  Serial.println("Stage 1: tone added on pin 8");

  // ЭТАП 2: подключаем серво на пин 7
  // myservo.attach(7);              // Этап 2
}

void loop() {
  // tone(8, 440, 100);              // Этап 1
  // delay(1000);

  for (int v = 0; v <= 255; v += 5) {
    for (int i = 0; i < NUM_LEDS; i++) analogWrite(PWM_PINS[i], v);
    delay(20);
  }
  for (int v = 255; v >= 0; v -= 5) {
    for (int i = 0; i < NUM_LEDS; i++) analogWrite(PWM_PINS[i], v);
    delay(20);
  }
}
