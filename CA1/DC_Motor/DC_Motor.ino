#define ON_OFF_PIN 8
#define INCREASE_SPEED_PIN 9
#define DECREASE_SPEED_PIN 10
#define TOGGLE_DIRECTION_PIN 11

int pwm = 255;
int last_pwm = 255;
int on_off_val = 0;
int inc_val = 0;
int dec_val = 0;
int tog_val = 0;

bool is_on_swtch_read = false;
bool is_inc_swtch_read = false;
bool is_dec_swtch_read = false;
bool is_tog_swtch_read = false;
bool motor_dir = false;

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
  on_off_swtch_program();
  inc_swtch_program();
  dec_swtch_program();
  tog_swtch_program();
 
  //actuate motor
  analogWrite(3, (motor_dir)?pwm:0);
  analogWrite(5, (motor_dir)?0:pwm);
}

void tog_swtch_program() {
  tog_val = digitalRead(TOGGLE_DIRECTION_PIN);
  if (tog_val == HIGH) {
    motor_dir = (is_tog_swtch_read)? motor_dir : !motor_dir;
    is_tog_swtch_read = true;
  }
  else {
    is_tog_swtch_read = false;
  }
}

void on_off_swtch_program() {
  on_off_val = digitalRead(ON_OFF_PIN);
  if (on_off_val == HIGH) {
    last_pwm = (!is_on_swtch_read)? last_pwm :(pwm != 0)? pwm : last_pwm;
    pwm = (is_on_swtch_read)? pwm :(pwm == 0) ? last_pwm : 0;
    is_on_swtch_read = true;
  }
  else {
    is_on_swtch_read = false;
  }
}



void dec_swtch_program() {
  dec_val = digitalRead(DECREASE_SPEED_PIN);
  if (dec_val == HIGH) {
    last_pwm = (is_dec_swtch_read)? last_pwm :(last_pwm - 10 < 0)? 0 : last_pwm - 10;
    pwm = (is_dec_swtch_read || pwm == 0)? pwm :(pwm - 10 < 0)? 0 : pwm - 10;
    is_dec_swtch_read = true;
  }
  else {
    is_dec_swtch_read = false;
  }
}
void inc_swtch_program() {
  inc_val = digitalRead(INCREASE_SPEED_PIN);
  if (inc_val == HIGH) {
    last_pwm = (is_inc_swtch_read)? last_pwm :(last_pwm + 10 > 255)? 255 : last_pwm + 10;
    pwm = (is_inc_swtch_read || pwm == 0)? pwm :(pwm + 10 > 255)? 255 : pwm + 10;
    is_inc_swtch_read = true;
  }
  else {
    is_inc_swtch_read = false;
  }
}
