/*
  MyButton.h - Library for encapsulating button states.
  Created by Christopher Wong, July 18, 2018.
*/

#ifndef MyButton_h
#define MyButton_h

#include "Arduino.h"
#include "MySimpleButtonStruct.h"

class MyButton
{
  public:
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

    const int NUM_OF_BUTTON_STATES = sizeof(btnStateStringPairs) / sizeof(ButtonStateStringPair);
    
    MyButton();
    void Initialize(MySimpleButtonStruct simpleBtnStruct);
    void Initialize(int id, String btnName, int pin);
    int getId();
    String getName();
    void myDigitalRead();
    ButtonState getState();
    String getStateStr();    

  private:
    /*
     * Somehow, the following would "upset" Arduino
     * const int MY_LOW = HIGH;
     * const int MY_HIGH = LOW;
     * So use 0 and 1 instead;
     */
    const int MY_LOW = 1;  // flipped
    const int MY_HIGH = 0;  // flipped
  
    int id;
    String btnName;
    int pin;
    int lastDigitalRead;
    int currentDigitalRead;

    String convertStateToStr(ButtonState state);
};

#endif


