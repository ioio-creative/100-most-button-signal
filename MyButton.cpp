/*
  MyButton.cpp - Library for encapsulating button states.
  Created by Christopher Wong, July 18, 2018.
*/

#include "MyButton.h"


/* constructors */

MyButton::MyButton() {  
  lastDigitalRead = LOW;
  currentDigitalRead = LOW;
}

/* end of constructors */


/* public methods */

void MyButton::Initialize(MyButton::ButtonId id, String btnName, int pin) {
  this->id = id;
  this->btnName = btnName;
  this->pin = pin;
}

String MyButton::getState(bool* isStateChanged) {
  lastDigitalRead = currentDigitalRead;
  currentDigitalRead = digitalRead(pin);
  *isStateChanged = lastDigitalRead != currentDigitalRead;
  
  ButtonState btnState;
  if (lastDigitalRead == LOW && currentDigitalRead == LOW) {
    btnState = NotPressed;
    Serial.println("NotPressed");
  } else if (lastDigitalRead == LOW && currentDigitalRead == HIGH) {
    btnState = Down;
    Serial.println("Down");
  } else if (lastDigitalRead == HIGH && currentDigitalRead == HIGH) {
    btnState = Pressed;
    Serial.println("Pressed");
  } else if (lastDigitalRead == HIGH && currentDigitalRead == LOW) {
    btnState = Up;
    Serial.println("Up");
  }

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
