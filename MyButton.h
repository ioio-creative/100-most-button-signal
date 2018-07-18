/*
  MyButton.h - Library for encapsulating button states.
  Created by Christopher Wong, July 18, 2018.
*/

#ifndef MyButton_h
#define MyButton_h

#include "Arduino.h"

class MyButton
{
  public:
    typedef enum
    {
      btnA = 0,
      btnB = 1,
      btnC = 2,
      btnD = 3,
      btnE = 4,
      btnF = 5,
      btnG = 6
    } ButtonId;

      typedef enum
    {
      NotPressed,
      Down,
      Pressed,      
      Up
    } ButtonState;

    struct ButtonStateStringPair
    {
      ButtonState state;
      String string;
    };

    // !!! Important !!! The number 4 is needed.
    // https://stackoverflow.com/questions/21152171/too-many-initializers-for-int-0-c
    ButtonStateStringPair btnStateStringPairs[4] = {
      { NotPressed, "N" },
      { Down, "D" },
      { Pressed, "P" },
      { Up, "U" }
    };

    const int NUM_OF_BUTTON_STATES = sizeof(btnStateStringPairs) / sizeof(MyButton::ButtonStateStringPair);
    
    MyButton();  
    void Initialize(MyButton::ButtonId id, String btnName, int pin);
    String getState(bool* isStateChanged);
    String getName();

  private:
    
  
    MyButton::ButtonId id;
    String btnName;
    int pin;
    int lastDigitalRead;
};

#endif


