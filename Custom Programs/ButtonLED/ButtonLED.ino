
// First I define the i/o pin numbers for the button and the LED 

#define button 9     
  
#define LED 6

// Then I initialize the button state as 0 (LOW / OFF) 

int button_state = 0;         

void setup() {

// Set the pinMode for both active pins
  pinMode(button, INPUT);

  pinMode(LED,OUTPUT);    //Sets the pinMode to Output 
}

void loop() {

// Set button_state based on state of button
  button_state = digitalRead(button);

// if button is pressed, turn on LED
  if(button_state == 1) {
   digitalWrite(LED, 1); 
  } else{
   digitalWrite(LED, 0);  
    }
}
