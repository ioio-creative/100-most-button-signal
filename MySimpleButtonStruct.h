#ifndef MySimpleButtonStruct_h
#define MySimpleButtonStruct_h

#include "Arduino.h"
#include "MyButton.h"

struct MySimpleButtonStruct
{
  int id;
  String btnName;
  int pin;
};

#endif
