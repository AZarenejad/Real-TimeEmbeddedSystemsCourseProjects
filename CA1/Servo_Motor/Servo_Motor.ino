#include <Servo.h>

#define CW_PIN 12
#define CCW_PIN 13

Servo servo;

double pos = 90;
int decVal = 0;
int incVal = 0;
bool isIncSwtchRead = false;
bool isDecSwtchRead = false;

void setup() {
  servo.attach(6);
  pinMode(CW_PIN, INPUT);
  pinMode(CCW_PIN, INPUT);
  servo.write(pos);
}

void loop() {
  incSwtchProgram();
  decSwtchProgram();
}

void incSwtchProgram() {
  incVal = digitalRead(CW_PIN);
  if (incVal == HIGH && !isIncSwtchRead) {
    Serial.println("INC");
    pos += 1.125;
    servo.write(pos);
    isIncSwtchRead = true;
  }
  else {
    isIncSwtchRead = incVal == HIGH;
  }
}

void decSwtchProgram() {
  decVal = digitalRead(CCW_PIN);
  if (decVal == HIGH && !isDecSwtchRead) {
    pos -= 1.125;
    servo.write(pos);
    isDecSwtchRead = true;
  }
  else {
    isDecSwtchRead = decVal == HIGH;
  }
}
