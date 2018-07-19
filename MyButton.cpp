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
void MyButton::Initialize(MySimpleButtonStruct simpleBtnStruct) {
  Initialize(simpleBtnStruct.id, simpleBtnStruct.btnName, simpleBtnStruct.pin);
}

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
  if (lastDigitalRead == MY_LOW && currentDigitalRead == MY_LOW) {
    btnState = NotPressed;
  } else if (lastDigitalRead == MY_LOW && currentDigitalRead == MY_HIGH) {
    btnState = Down;
  } else if (lastDigitalRead == MY_HIGH && currentDigitalRead == MY_HIGH) {
    btnState = Pressed;    
  } else if (lastDigitalRead == MY_HIGH && currentDigitalRead == MY_LOW) {
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
