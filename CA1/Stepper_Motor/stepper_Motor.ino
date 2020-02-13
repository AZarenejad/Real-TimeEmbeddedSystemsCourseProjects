#define CW_PIN 13
#define CCW_PIN 12
#define OFF_PIN 11
int n = 8;
bool rotateCW = true;
bool isOff = false;

bool isCwRead = false;
int cwVal = 0;

bool isCcwRead = false;
int ccwVal = 0;

bool isOffRead = false;
int offVal = 0;

void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(CW_PIN, INPUT); //cw
  pinMode(CCW_PIN, INPUT); //ccw
  pinMode(OFF_PIN, INPUT); //off
}

void loop() {
  //buttons
  cwSwtchProgram();
  ccwSwtchProgram();
  offSwtchProgram();

  //actuate motor
  if (rotateCW && !isOff) n = n >> 1;
  else if (!isOff) n = n << 1;
  if(n == 0) n = 8;
  if(n >= 16) n = 1;
  if (!isOff) motorCommand(n);
  delay(300);
}

void cwSwtchProgram() {
  cwVal = digitalRead(CW_PIN);
  if (cwVal == HIGH) {
    rotateCW = (isCwRead)? rotateCW : true;
    isOff = (isCwRead)? isOff : false;
    isCwRead = true;
  }
  else isCwRead = false;
}

void ccwSwtchProgram() {
  ccwVal = digitalRead(CCW_PIN);
  if (ccwVal == HIGH) {
    rotateCW = (isCcwRead)? rotateCW : false;
    isOff = (isCcwRead)? isOff : false;
    isCcwRead = true;
  }
  else isCcwRead = false;
}

void offSwtchProgram() {
  offVal = digitalRead(OFF_PIN);
  if (offVal == HIGH) {
    isOff = (isOffRead)? isOff : true;
    isOffRead = true;
  }
  else isOffRead = false;
}

void motorCommand(int command) {
  digitalWrite(4, command%2);
  digitalWrite(5, (command>>1)%2);
  digitalWrite(6, (command>>2)%2);
  digitalWrite(7, (command>>3)%2);
}


