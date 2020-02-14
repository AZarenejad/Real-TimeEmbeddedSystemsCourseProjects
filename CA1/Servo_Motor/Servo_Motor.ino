#include <Servo.h>

#define CW_PIN 12
#define CCW_PIN 13

Servo servo;

double pos = 90;
int dec_val = 0;
int inc_val = 0;
bool is_inc_swtch_read = false;
bool is_dec_swtch_read = false;

void setup() {
  servo.attach(6);
  pinMode(CW_PIN, INPUT);
  pinMode(CCW_PIN, INPUT);
  servo.write(pos);
}

void loop() {
  inc_swtch_program();
  dec_swtch_program();
}

void dec_swtch_program() {
  dec_val = digitalRead(CCW_PIN);
  if (dec_val == HIGH && !is_dec_swtch_read) {
    pos -= 1.125;
    servo.write(pos);
    is_dec_swtch_read = true;
  }
  else {
    is_dec_swtch_read = dec_val == HIGH;
  }
}

void inc_swtch_program() {
  inc_val = digitalRead(CW_PIN);
  if (inc_val == HIGH && !is_inc_swtch_read) {
    Serial.println("INC");
    pos += 1.125;
    servo.write(pos);
    is_inc_swtch_read = true;
  }
  else {
    is_inc_swtch_read = inc_val == HIGH;
  }
}
