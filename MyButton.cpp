/*
  MyButton.cpp - Library for encapsulating button states.
  Created by Christopher Wong, July 18, 2018.
*/

#include "MyButton.h"


/* constructors */

MyButton::MyButton() {  
  lastDigitalRead = LOW;
}

/* end of constructors */


/* public methods */

// call Initialize() in setup()
void MyButton::Initialize(int anId, String aBtnName, int aPin) {
  id = anId;
  btnName = aBtnName;
  pin = aPin;

  // !!! Important !!!
  pinMode(aPin, INPUT_PULLUP);
}

String MyButton::getName() {
  return btnName;
}

MyButton::ButtonState MyButton::getState(bool* isStateChanged) {  
  int currentDigitalRead = digitalRead(pin);
  *isStateChanged = lastDigitalRead != currentDigitalRead;

//  if (btnName == "btnG") {
//    Serial.println(currentDigitalRead);
//  }

  // !!! Important !!! Somehow the digitalRead is inverted
  ButtonState btnState;
  if (!(lastDigitalRead == LOW && currentDigitalRead == LOW)) {
    btnState = NotPressed;
  } else if (!(lastDigitalRead == LOW && currentDigitalRead == HIGH)) {
    btnState = Down;
  } else if (!(lastDigitalRead == HIGH && currentDigitalRead == HIGH)) {
    btnState = Pressed;    
  } else if (!(lastDigitalRead == HIGH && currentDigitalRead == LOW)) {
    btnState = Up;
  }

  lastDigitalRead = currentDigitalRead;

  return btnState;
}

String MyButton::getStateStr(bool* isStateChanged) {
  return convertStateToStr(getState(isStateChanged));
}

/* end of public methods */


/* private methods */

String MyButton::convertStateToStr(ButtonState state) {
  String stateStr = "";
  for (int i = 0; i < NUM_OF_BUTTON_STATES; i++) {
    ButtonStateStringPair btnStateStringPair = btnStateStringPairs[i];
    if (state == btnStateStringPair.state) {
      stateStr = btnStateStringPair.string;
    }
  } 
  return stateStr;
}

/* end of private methods */
