//For use with GITADORA Selection Panel 
//This sketch maps 8 buttons,4x3 keypad button and  blinking LED
//This sketch file is for use with Arduino Leonardo
//
//By kaze892
//2020-06-22

#include <Keypad.h>
#include <Joystick.h>

#define ENABLE_PULLUPS
#define NUMROWS 4
#define NUMCOLS 3

// Pins allocation for keypad
byte rowPins[NUMROWS] = {21,20,19,18}; 
byte colPins[NUMCOLS] = {15,14,16}; 

byte buttons[NUMROWS][NUMCOLS] = {
  //Keypad Button allocation
  {8,9,10},
  {11,12,13},
  {14,15,16},
  {17,18,19},
};

//initialize an instance of class NewKeypad
Keypad buttbx = Keypad( makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS); 


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK, 
  20, 0,                 // Button Count, No Hat Switch Count
  false, false, false,   // No X, Y and Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering


void setup() {
  
  // Initialize Pins
  // Pins 2 to 9 -> UP,DOWN,LEFT,RIGHT,START,HELP,SERVICE,TEST
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  
  //Pin 10 to LED
  pinMode(10, OUTPUT);
  
  // Initialize Joystick Library
  Joystick.begin();
}
  
// Constant that maps the phyical pin to the joystick button.
const int pinToButtonMap = 2;

// Last state of the button
int lastButtonState[8] = {0,0,0,0,0,0,0,0};

void loop() { 

  //Call function to map UP,DOWN,LEFT,RIGHT,START,HELP
  CheckAllButtons1();
  
  //Call function to map keypad
  CheckAllButtons2();
  
  //Makes Pin10 led blink in values of 1000ms
  digitalWrite(10, (millis() / 1000) % 2);

}

void CheckAllButtons1(void) {
    // Read pin values from pinToButtonMap to lastButtonState
  for (int i = 0; i < 8; i++)
  {
    int currentButtonState = !digitalRead(i + pinToButtonMap);
    if (currentButtonState != lastButtonState[i])
    {
      Joystick.setButton(i, currentButtonState);
      lastButtonState[i] = currentButtonState;
    }
  }
  delay(50);
}

void CheckAllButtons2(void) {
   //Read pin values from Rows and Cols
      if (buttbx.getKeys())
    {
       for (int i=0; i<LIST_MAX; i++)   
        {
           if ( buttbx.key[i].stateChanged )   
            {
            switch (buttbx.key[i].kstate) {  
                    case PRESSED:
                    case HOLD:
                              Joystick.setButton(buttbx.key[i].kchar, 1);
                              break;
                    case RELEASED:
                    case IDLE:
                              Joystick.setButton(buttbx.key[i].kchar, 0);
                              break;
            }
           }   
         }
     }
}
