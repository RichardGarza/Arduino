
// First I define the i/o pin numbers for the button and the LED 

#define button 9     
  
#define LED 6

// Then I initialize the button state as 0 (LOW / OFF) 

int button_state = 0;         
int pin3OUTPUT = 0;       

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
