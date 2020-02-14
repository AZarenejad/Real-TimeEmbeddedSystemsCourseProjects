#define CW_PIN 13
#define CCW_PIN 12
#define OFF_PIN 11
int n = 8;
bool rotate_cw = true;
bool is_off = false;

bool is_cw_read = false;
int cw_val = 0;

bool is_ccw_read = false;
int ccw_val = 0;

bool is_off_read = false;
int off_val = 0;

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
  cw_swtch_program();
  ccw_swtch_program();
  off_swtch_program();

  //actuate motor
  if (rotate_cw && !is_off) n = n >> 1;
  else if (!is_off) n = n << 1;
  if(n == 0) n = 8;
  if(n >= 16) n = 1;
  if (!is_off) motor_command(n);
  delay(300);
}

void cw_swtch_program() {
  cw_val = digitalRead(CW_PIN);
  if (cw_val == HIGH) {
    rotate_cw = (is_cw_read)? rotate_cw : true;
    is_off = (is_cw_read)? is_off : false;
    is_cw_read = true;
  }
  else is_cw_read = false;
}

void ccw_swtch_program() {
  ccw_val = digitalRead(CCW_PIN);
  if (ccw_val == HIGH) {
    rotate_cw = (is_ccw_read)? rotate_cw : false;
    is_off = (is_ccw_read)? is_off : false;
    is_ccw_read = true;
  }
  else is_ccw_read = false;
}

void off_swtch_program() {
  off_val = digitalRead(OFF_PIN);
  if (off_val == HIGH) {
    is_off = (is_off_read)? is_off : true;
    is_off_read = true;
  }
  else is_off_read = false;
}

void motor_command(int command) {
  digitalWrite(4, command%2);
  digitalWrite(5, (command>>1)%2);
  digitalWrite(6, (command>>2)%2);
  digitalWrite(7, (command>>3)%2);
}
