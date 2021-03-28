///////////////////////////////////// RECORDING STUIDIO SMART SWITCH ////////////////////////////////////////////////

///////////////////////////////////// LIBRARY DECLARATIONS /////////////////////////////////////////////////////////

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

///////////////////////////////////// VARIABLE DECLARATIONS /////////////////////////////////////////////////////////

// First I define the i/o pin numbers for the button and the LCD Screen

#define OFF_btn 2
#define ON_btn 3
#define REC_btn 4

#define RLY_ONE 5
#define RLY_TWO 6

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// Then I define the initial button states as HIGH since I'm using the
// internal pullup resistors and I initialize the relay states as LOW
// so they are off when the program starts.

int OFF_btn_state = HIGH;
int ON_btn_state = HIGH;
int REC_btn_state = HIGH;

// Now I'll initialize a global state variable and set it to OFF.
// Since I'll have 3 global states, I'm using 1, 2, and 3 for simplicity.
// 1 = OFF, 2 = ON, 3 = REC

int GLOBAL_state = 1;


///////////////////////////////////// CUSTOM FUNCTION DECLARATIONS ///////////////////////////////////////////////////

// I'll define the set_global_state function
int Set_global_state (int x) {
  GLOBAL_state = x;
}

// and I'll define the reset function (just in case)
void(* resetFunc) (void) = 0;

// then I define the function to prepare screen for printing
void setupScreenToPrint(void) {
  display.clearDisplay();
  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(50, 6);            // Start at top-left corner
}

// This will print 'On' to the display
void printON(void) {
  display.println(F("On"));
  display.display();
  delay(2000);
}

// This will print 'Off' to the display
void printOFF(void) {
  display.println(F("Off"));
  display.display();
  delay(2000);
}

// This will print 'Rec' to the display
void printREC(void) {
  display.println(F("Rec"));
  display.display();
  delay(1500);
}

// This will clear the display
void printNothing(void) {
  display.println(F(""));
  display.display();
  delay(1500);
}


///////////////////////////////////// SETUP FUNCTION ////////////////////////////////////////////////////////////////

// Now I'll define the setup function
void setup() {
  Serial.begin(9600);
  
  // Then Set the pinMode for inputs
  pinMode(OFF_btn, INPUT_PULLUP);
  pinMode(ON_btn, INPUT_PULLUP);
  pinMode(REC_btn, INPUT_PULLUP);

  // Then Set the pinMode for outputs
  pinMode(RLY_ONE, OUTPUT);
  pinMode(RLY_TWO, OUTPUT);

  // Make sure relays are off
  digitalWrite(RLY_ONE, HIGH);
  digitalWrite(RLY_TWO, HIGH);

  // Then I rotate screen 180 degrees & clear display
  display.setRotation(2);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Then I output "OFF" to the LCD Screen
  setupScreenToPrint();
  printOFF();
}

///////////////////////////////////// LOOP FUNCTION /////////////////////////////////////////////////////////////////

// Now I'll implement the logic for what I want the program to do.
void loop() {
  int previous_state = GLOBAL_state;

  // First I read the state of each button & store the result in a variable
  OFF_btn_state = digitalRead(OFF_btn);
  ON_btn_state = digitalRead(ON_btn);
  REC_btn_state = digitalRead(REC_btn);

  // Then I'll compare the following:
  // Is a button being pressed?
  // Is that button the only one being pressed?
  // Is the desired state already active?

  // Off button pressed
  if (
    OFF_btn_state == LOW &&
    ON_btn_state == HIGH &&
    REC_btn_state == HIGH  &&
    GLOBAL_state != 1
  ) {
    Set_global_state (1);
  }

  // On button pressed
  else if (
    OFF_btn_state == HIGH &&
    ON_btn_state == LOW &&
    REC_btn_state == HIGH  &&
    GLOBAL_state != 2
  ) {
    Set_global_state (2);
  }

  // Record button pressed
  else if (
    OFF_btn_state == HIGH &&
    ON_btn_state == HIGH &&
    REC_btn_state == LOW  &&
    GLOBAL_state != 3
  ) {
    Set_global_state (3);
  }

  // All three buttons pressed, reset device.
  else if (
    OFF_btn_state == LOW &&
    ON_btn_state == LOW &&
    REC_btn_state == LOW
  ) {
    resetFunc();
  }

  // Then I'll check if the state has changed based on the previous
  // if/else statement & activate the relays accordingly.

  if ( previous_state != GLOBAL_state) {

    if (GLOBAL_state == 1) {
      digitalWrite(RLY_ONE, HIGH);
      digitalWrite(RLY_TWO, HIGH);
      setupScreenToPrint();
      printOFF();
  
    } else if (GLOBAL_state == 2) {
      digitalWrite(RLY_ONE, LOW);
      digitalWrite(RLY_TWO, LOW);
      setupScreenToPrint();
      printON();
  
    } else if (GLOBAL_state == 3) {
      digitalWrite(RLY_ONE, LOW);
      digitalWrite(RLY_TWO, HIGH);
      setupScreenToPrint();
      printREC();
    }

    // Update the LCD Screen with new state
    // Make 'Recording' Blink on screen when active.
  }

    // While in recording state, blink the 'Rec' on screen
  if( previous_state == 3 && GLOBAL_state == 3) {
    setupScreenToPrint();
    printNothing();
    setupScreenToPrint();
    printREC();
  }
  // End Loop
}
