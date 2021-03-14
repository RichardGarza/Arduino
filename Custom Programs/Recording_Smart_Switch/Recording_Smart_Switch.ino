// First I define the i/o pin numbers for the button and the LED 

#define OFF_btn 2     
#define ON_btn 3     
#define REC_btn 4     

#define RLY_ONE 5    
#define RLY_TWO 6 
   
#define LED_SCREEN 7    



// Then I define the initial button states as HIGH since I'm using the 
// internal pullup resistors and I initialize the relay states as LOW 
// so they are off when the program starts.

int OFF_btn_state = HIGH;         
int ON_btn_state = HIGH;         
int REC_btn_state = HIGH;

int RLY_ONE_state = LOW;
int RLY_TWO_state = LOW;



// Now I'll initialize the global state as OFF. 
// Since I'll have 3 global states, I'm using 1, 2, and 3 for simplicity. 
// 1 = OFF, 2 = ON, 3 = REC

int GLOBAL_state = 1;

// and I'll define the set_global_state function
int Set_global_state (int x){
  GLOBAL_state = x;
}



// Now I'll define the setup function
void setup() {

// First I'll initialize my serial connection
// (The serial connection is temporary for programming/debugging) 

// Init serial connection
  Serial.begin(9600);

// Then Set the pinMode for inputs
  pinMode(OFF_btn, INPUT_PULLUP);
  pinMode(ON_btn, INPUT_PULLUP);
  pinMode(REC_btn, INPUT_PULLUP);  

// Then Set the pinMode for outputs
  pinMode(RLY_ONE,OUTPUT);
  pinMode(RLY_TWO,OUTPUT);
  pinMode(LED_SCREEN,OUTPUT);

// Then I output "OFF" to the LED Screen
}



// Now I'll define the loop function
void loop() {
  int previous_state = GLOBAL_state;

// First I read the state of each button
  OFF_btn_state = digitalRead(OFF_btn);         
  ON_btn_state = digitalRead(ON_btn);         
  REC_btn_state = digitalRead(REC_btn);

// Then I'll compare the following: 
// Is a button being pressed? 
// Is that button the only one being pressed? 
// Is the desired state already active? 

// Off button pressed
  if(
    OFF_btn_state == LOW &&
    ON_btn_state == HIGH &&
    REC_btn_state == HIGH  &&
    GLOBAL_state != 1
    ){
    Set_global_state (1); 
  } 

// On button pressed
  else if (
    OFF_btn_state == HIGH &&
    ON_btn_state == LOW &&
    REC_btn_state == HIGH  &&
    GLOBAL_state != 2
    ){
    Set_global_state (2); 
  } 

// Record button pressed
  else if (
    OFF_btn_state == HIGH &&
    ON_btn_state == HIGH &&
    REC_btn_state == LOW  &&
    GLOBAL_state != 3
    ){
    Set_global_state (3);
  }

// Then I'll check if the state has changed based on the previous
// if/else statement & activate the relays accordingly.

  if( previous_state != GLOBAL_state){
  
    if(GLOBAL_state == 1){
      digitalWrite(RLY_ONE, LOW);
      digitalWrite(RLY_TWO, LOW);
    } else if (GLOBAL_state == 2){
      digitalWrite(RLY_ONE, HIGH);
      digitalWrite(RLY_TWO, HIGH);
    } else if (GLOBAL_state == 3){
      digitalWrite(RLY_ONE, HIGH);
      digitalWrite(RLY_TWO, LOW);
    }

// Update the LED Screen with new state
  
  }
// End Loop
}
