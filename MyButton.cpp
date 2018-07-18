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
void MyButton::Initialize(MyButton::ButtonId anId, String aBtnName, int aPin) {
  id = anId;
  btnName = aBtnName;
  pin = aPin;

  // !!! Important !!!
  pinMode(aPin, INPUT_PULLUP);
}

String MyButton::getState(bool* isStateChanged) {  
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

  String stateStr = "";
  for (int i = 0; i < NUM_OF_BUTTON_STATES; i++) {
    ButtonStateStringPair btnStateStringPair = btnStateStringPairs[i];
    if (btnState == btnStateStringPair.state) {
      stateStr = btnStateStringPair.string;
    }
  }
  
  return stateStr;
}

String MyButton::getName() {
  return btnName;
}

/* end of public methods */


/* private methods */

/* end of private methods */
