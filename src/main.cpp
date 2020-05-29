#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "motor.hpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define MOTOR_FORWARD PA_2
#define MOTOR_REVERSE PA_3
#define SPEED_IN PB1
Motor::DCMotor m(MOTOR_FORWARD, MOTOR_REVERSE);

#define PWMFREQ 2000

void setup() {
  pinMode(MOTOR_FORWARD, OUTPUT);
  pinMode(MOTOR_REVERSE, OUTPUT);
  pinMode(SPEED_IN, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.display();
}

void loop() {
  int speed = analogRead(SPEED_IN);
  int forward = speed > 512 ? (speed - 512) * 2 : 0;
  int reverse = speed <= 512 ? (512 - speed) * 2 : 0;
  pwm_start(MOTOR_FORWARD, PWMFREQ, forward, RESOLUTION_10B_COMPARE_FORMAT);
  pwm_start(MOTOR_REVERSE, PWMFREQ, reverse, RESOLUTION_10B_COMPARE_FORMAT);

  display.clearDisplay();
  display.setCursor(0, 0);
  if (forward != 0) {
    display.printf("Speed: %d\n", forward);
    display.printf("Dir: f\n");
  } else {
    display.printf("Speed: %d\n", reverse);
    display.printf("Dir: b\n");
  }
  display.display();
  delay(100);
}
