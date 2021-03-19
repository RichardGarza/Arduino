#define OFF_btn 2
#define ON_btn 3
#define REC_btn 4

int OFF_btn_state = HIGH;
int ON_btn_state = HIGH;
int REC_btn_state = HIGH;

void setup() {

// Init serial connection
  Serial.begin(9600);
  Serial.println("Serial Connection Established...");

  // Then Set the pinMode for inputs
  pinMode(OFF_btn, INPUT_PULLUP);
  pinMode(ON_btn, INPUT_PULLUP); 
  pinMode(REC_btn, INPUT_PULLUP);

}

void loop() {

  // First I read the state of each button & store the result in a variable
  OFF_btn_state = digitalRead(OFF_btn);
  ON_btn_state = digitalRead(ON_btn);
  REC_btn_state = digitalRead(REC_btn);


  if (
    OFF_btn_state == LOW  
  ) {
    Serial.println("1");
    delay(300);
  }

  if (
    ON_btn_state == LOW   
  ) {
    Serial.println("2");
    delay(300);
  }

  if (
    REC_btn_state == LOW  
  ) {
    Serial.println("3");
    delay(300);
  }
}
