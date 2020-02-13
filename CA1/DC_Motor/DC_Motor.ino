#define ON_OFF_PIN 8
#define INCREASE_SPEED_PIN 9
#define DECREASE_SPEED_PIN 10
#define TOGGLE_DIRECTION_PIN 11

int pwm = 255;
int lastPwm = 255;
int onOffVal = 0;
int incVal = 0;
int decVal = 0;
int togVal = 0;

bool isOnSwtchRead = false;
bool isIncSwtchRead = false;
bool isDecSwtchRead = false;
bool isTogSwtchRead = false;
bool motorDir = false;

void setup() {
  pinMode(ON_OFF_PIN, INPUT);
  pinMode(INCREASE_SPEED_PIN, INPUT);
  pinMode(DECREASE_SPEED_PIN, INPUT);
  pinMode(TOGGLE_DIRECTION_PIN, INPUT);

  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  //buttons
  onOffSwtchProgram();
  incSwtchProgram();
  decSwtchProgram();
  togSwtchProgram();
 
  //actuate motor
  analogWrite(3, (motorDir)?pwm:0);
  analogWrite(5, (motorDir)?0:pwm);
}

void onOffSwtchProgram() {
  onOffVal = digitalRead(ON_OFF_PIN);
  if (onOffVal == HIGH) {
    lastPwm = (!isOnSwtchRead)? lastPwm :(pwm != 0)? pwm : lastPwm;
    pwm = (isOnSwtchRead)? pwm :(pwm == 0) ? lastPwm : 0;
    isOnSwtchRead = true;
  }
  else {
    isOnSwtchRead = false;
  }
}

void incSwtchProgram() {
  incVal = digitalRead(INCREASE_SPEED_PIN);
  if (incVal == HIGH) {
    lastPwm = (isIncSwtchRead)? lastPwm :(lastPwm + 10 > 255)? 255 : lastPwm + 10;
    pwm = (isIncSwtchRead || pwm == 0)? pwm :(pwm + 10 > 255)? 255 : pwm + 10;
    isIncSwtchRead = true;
  }
  else {
    isIncSwtchRead = false;
  }
}

void decSwtchProgram() {
  decVal = digitalRead(DECREASE_SPEED_PIN);
  if (decVal == HIGH) {
    lastPwm = (isDecSwtchRead)? lastPwm :(lastPwm - 10 < 0)? 0 : lastPwm - 10;
    pwm = (isDecSwtchRead || pwm == 0)? pwm :(pwm - 10 < 0)? 0 : pwm - 10;
    isDecSwtchRead = true;
  }
  else {
    isDecSwtchRead = false;
  }
}

void togSwtchProgram() {
  togVal = digitalRead(TOGGLE_DIRECTION_PIN);
  if (togVal == HIGH) {
    motorDir = (isTogSwtchRead)? motorDir : !motorDir;
    isTogSwtchRead = true;
  }
  else {
    isTogSwtchRead = false;
  }
}

