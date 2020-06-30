#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include "motor.hpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define MOTOR_FORWARD PA_1
#define MOTOR_REVERSE PA_0
#define SPEED_IN PA4
Motor::DCMotor motor(MOTOR_FORWARD, MOTOR_REVERSE, 512);

#define PWMFREQ 2000

void setup() {
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
  motor.setSpeed((speed - 512) / 512.0);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.printf("Speed: %d\n", (int) (motor.getSpeed() * 100));
  display.printf("Dir: %c\n", motor.getDirection() == Motor::Direction::Forward ? 'f' : 'b');
  display.display();
  delay(100);
}
