// First I define the i/o pin numbers for the button and the LED 

#define OFF_btn 2     
#define ON_btn 3     
#define REC_btn 4     

#define RLY_ONE 5    
#define RLY_TWO 6 
   
#define LED_SCREEN 7    


// Then I initialize the button states as HIGH since I'm using the 
// internal pullup resistors and I initialize the relay states as LOW.

int OFF_btn_state = HIGH;         
int ON_btn_state = HIGH;         
int REC_btn_state = HIGH;

int RLY_ONE_state = LOW;
int RLY_TWO_state = LOW;

// Now I'll initialize the global state as OFF. 
// Since I'll have 3 global states, I'm using 1, 2, and 3 for simplicity. 
// 1 = OFF, 2 = ON, 3 = REC

int GLOBAL_state = 1;

void setup() {

  Serial.begin(9600);

// Set the pinMode for both active pins
  pinMode(button, INPUT_PULLUP);
  pinMode(3,OUTPUT);
  pinMode(LED,OUTPUT);    //Sets the pinMode to Output 
}


void loop() {

// Set button_state based on state of button
  button_state = digitalRead(button);

  Serial.println(button_state);
  delay(1000);

  if(pin3OUTPUT == 0){
    digitalWrite(3, 1);
    pin3OUTPUT = 1;
  } else {
    digitalWrite(3,0);
    pin3OUTPUT = 0;
  }

  
// if button is pressed, turn on LED
  if(button_state == 1) {
   digitalWrite(LED, 1); 
  } else{
   digitalWrite(LED, 0);  
    }
}
