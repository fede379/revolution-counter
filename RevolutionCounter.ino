#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3
#define SENSOR 7
#define BUTTON 8

int counter = 0;
int state = 0;
int stateAnt = 0;
int buttonState = 0;
bool revMode = false;

const uint8_t SEG_REV[] = {
  SEG_G,                                           // -
  SEG_E | SEG_G,                                   // r  
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,           // E
  SEG_C | SEG_D | SEG_E                            // v
  };
  
const uint8_t SEG_NORM[] = {
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_E | SEG_G,                                   // r
  SEG_G                                            // -
  };

TM1637Display display(CLK, DIO);

void setup() {
  //pinMode(SENSOR, INPUT);
  display.setBrightness(7, true); // Turn on
  display.showNumberDec(counter, false); // Expect: ___0
}

void loop() {
  display.showNumberDec(counter, false);
  buttonState = digitalRead(BUTTON);
  if (buttonState == HIGH) {
    revMode = !revMode;
    if(revMode == true) {
      display.setSegments(SEG_REV);
    } else {
      display.setSegments(SEG_NORM);
    }
    delay(1000);
  }
  state = digitalRead(SENSOR);
  if (state == LOW && state != stateAnt) {
    if (revMode == false) {
      counter++;
    } else {
      counter--;
    }    
  }
  stateAnt = digitalRead(SENSOR);
}
