/*
   Web client sketch for IDE v1.0.1 and w5100/w5200
   Uses POST method.
   Posted November 2012 by SurferTim
*/

/*
 * Web Client POST method request (Ethernet.h)
 * https://playground.arduino.cc/Code/WebClient
 * 
 * Arduino Ethernet Shield W5100
 * https://detail.tmall.com/item.htm?spm=a230r.1.14.6.180651137c6SBp&id=38628268194&cm_id=140105335569ed55e27b&abbucket=1
 * 
 * Modified by Christopher Wong and Wong Chun Hoi
 */


 /* includes */

#include <SPI.h>
#include <Ethernet.h>

#include "MyButton.h"

/* end of includes */


/* networking params */

//const byte mac[] = {  
//  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
uint8_t mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

//Change to your server domain
//const char serverName[] = "www.mydomain.com";
//const char serverName[] = "localhost";
//const char serverName[] = "54.251.190.138";
const char serverName[] = "172.20.0.11";

// change to your server's port
//const int serverPort = 8080;
const int serverPort = 80;

// change to the pathName on that server
//const char pathName[] = "/api/test";
const char pathName[] = "/print.php";

/* end of networking params */


/* global variables for networking */

EthernetClient client;
int totalCount = 0;
// insure data is big enough to hold your variables
char data[64];

/* end of global variables for networking */


/* button params */

const MySimpleButtonStruct simpleButtonStructs[] = {
  { 1, "a", 2 },
  { 2, "b", 3 },
  { 3, "c", 5 },
  { 4, "d", 6 },
  { 5, "e", 7 },
  { 6, "f", 8 },
  { 7, "g", 9 }
};

const int NUM_OF_BUTTONS = sizeof(simpleButtonStructs) / sizeof(MySimpleButtonStruct);

MyButton buttons[NUM_OF_BUTTONS];

/* end of button params */


/* timer params */

//// set this to the number of milliseconds delay
//// this is 30 seconds
//#define delayMillis 30000UL
//
//unsigned long thisMillis = 0;
//unsigned long lastMillis = 0;

/* end of timer params */


void setup() {
  Serial.begin(9600);

  // disable SD SPI
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  Serial.print(F("Starting ethernet..."));

//  if(!Ethernet.begin(mac)) Serial.println(F("failed"));
//  else Serial.println(Ethernet.localIP());

  // specify ip if dhcp not available
  IPAddress myIp(172, 20, 0, 12);
  Ethernet.begin(mac, myIp);

  delay(2000);
  Serial.println(F("Ready"));

  for (int i = 0; i < NUM_OF_BUTTONS; i++) {
    buttons[i].Initialize(simpleButtonStructs[i]); 
  }
}

void loop() {
  // If using a static IP, comment out the next line
  Ethernet.maintain();

//  thisMillis = millis();
//
//  if(thisMillis - lastMillis > delayMillis)
//  {
//    lastMillis = thisMillis;
//  }

  //sendButtonSignalToServer(getButtonClicked());

  //sendButtonSignalToServer(buttons);

  getAndSendButtonStates(buttons);
}


/* testing sendButtonSignalToServer using input from Serial */

//int getButtonClicked() {
//  int inChar = -1;
//  if (Serial.available() > 0) {
//    inChar = Serial.read();
//    Serial.println(inChar);
//  }
//  return convertAsciiValueToNumberCharacter(inChar);
//}
//
//int convertAsciiValueToNumberCharacter(int asciiValue) {
//  // 48 = 0 in ASCII
//  return asciiValue - 48;
//}

//void sendButtonSignalToServer(int btnId) {  
//  if (btnId > 0 && btnId < 8) {  
//    sprintf(data, "{\"btnPressed\": %d}", btnId);
//    if(!postJson(serverName,serverPort,pathName,data)) Serial.print(F("Fail "));
//    else Serial.print(F("Pass "));
//    totalCount++;
//    Serial.println(totalCount,DEC);
//  }
//}

/* end of testing sendButtonSignalToServer using input from Serial */


void getAndSendButtonStates(MyButton buttons[]) {
  buttonsDigitalRead(buttons);

  sendButtonSignalToServer(buttons);
  
  buttonsUpdateLastDigitalRead(buttons);
}


void buttonsDigitalRead(MyButton buttons[]) {
  for (int i = 0; i < NUM_OF_BUTTONS; i++) {
    buttons[i].myDigitalRead();
//    if (buttons[i].getName() == "g") {
//      bool dummy;
//      Serial.println(buttons[i].getStateStr(&dummy));
//    }
  }
}

void buttonsUpdateLastDigitalRead(MyButton buttons[]) {
  for (int i = 0; i < NUM_OF_BUTTONS; i++) {
    buttons[i].updateLastDigitalRead();
  }
}

void sendButtonSignalToServer(MyButton buttons[]) {
  String jsonStr;
  
//  jsonStr = constructAllButtonsJsonData(buttons);
//  Serial.println(jsonStr);

  bool doesDownButtonExist = false;
  jsonStr = constructDownButtonsJsonData(buttons, &doesDownButtonExist);
//  sprintf(data, jsonStr.c_str());
//  Serial.println(data);
    
  if (doesDownButtonExist) {
      sprintf(data, jsonStr.c_str());
      Serial.println(data);   
    if (!postJson(serverName, serverPort, pathName, data)) {
      Serial.print(F("Fail "));
    } else {
      Serial.print(F("Pass "));
    }
    totalCount++;
    Serial.println(totalCount, DEC);
  }
}

String constructDownButtonsJsonData(MyButton buttons[], bool* doesDownButtonExist) {
  String delimiter = ",";
  String json = "{\"down\":[";
  for (int i = 0; i < NUM_OF_BUTTONS; i++) {
    MyButton myBtn = buttons[i];
    if (myBtn.getState() == MyButton::Down) {
      json += String(myBtn.getId()) + delimiter;
      *doesDownButtonExist = true;
    }
  }
  // remove trailing delimiter
  if (json.indexOf(delimiter) > 0) {
    json.remove(json.length() - delimiter.length());
  }
  json += "]}";
  return json;
}

String constructAllButtonsJsonData(MyButton buttons[]) {
  String json = "{";
  for (int i = 0; i < NUM_OF_BUTTONS; i++) {
    MyButton myBtn = buttons[i];
    json += "\"" + myBtn.getName() + "\":" + myBtn.getStateStr() + ",";
  }
  json += "}";
  return json;
}

byte postJson(const char* domainBuffer, int thisPort, const char* path, const char* jsonData) {
  int inChar;
  char outBuf[64];

  Serial.print(F("connecting..."));

  if(client.connect(domainBuffer,thisPort) == 1)
  {
    Serial.println(F("connected"));

    // send the header
    sprintf(outBuf,"POST %s HTTP/1.1",path);
    client.println(outBuf);
    sprintf(outBuf,"Host: %s",domainBuffer);
    client.println(outBuf);
    client.println(F("Connection: close\r\nContent-Type: application/json"));
    sprintf(outBuf,"Content-Length: %u\r\n",strlen(jsonData));
    client.println(outBuf);
    
    // send the body (variables)
    client.print(jsonData);       
  }
  else
  {
    Serial.println(F("failed"));
    return 0;
  }

  int connectLoop = 0;

  while(client.connected())
  {
    while(client.available())
    {
      inChar = client.read();
      Serial.write(inChar);
      connectLoop = 0;
    }

    delay(1);
    connectLoop++;
    if(connectLoop > 10000)
    {
      Serial.println();
      Serial.println(F("Timeout"));
      client.stop();
    }
  }

  Serial.println();
  Serial.println(F("disconnecting."));
  client.stop();
  return 1;
}
