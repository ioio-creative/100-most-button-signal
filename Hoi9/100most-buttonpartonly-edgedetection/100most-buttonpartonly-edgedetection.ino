//Arduino Code for 100most button
const int btnPinA = 2;
const int btnPinB = 3;
const int btnPinC = 5;
const int btnPinD = 6;
const int btnPinE = 7;
const int btnPinF = 8;
const int btnPinG = 9;



int btnStateA = 0;
int btnStateB = 0;
int btnStateC = 0;
int btnStateD = 0;
int btnStateE = 0;
int btnStateF = 0;
int btnStateG = 0;

int lastBtnStateA = 0;
int lastBtnStateB = 0;
int lastBtnStateC = 0;
int lastBtnStateD = 0;
int lastBtnStateE = 0;
int lastBtnStateF = 0;
int lastBtnStateG = 0;


int delayConst = 500;



void setup() {
  // put your setup code here, to run once:
  pinMode(btnPinA, INPUT_PULLUP);
  pinMode(btnPinB, INPUT_PULLUP);
  pinMode(btnPinC, INPUT_PULLUP);
  pinMode(btnPinD, INPUT_PULLUP);
  pinMode(btnPinE, INPUT_PULLUP);
  pinMode(btnPinF, INPUT_PULLUP);
  pinMode(btnPinG, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // updating the button states
  btnStateA = digitalRead(btnPinA);
  btnStateB = digitalRead(btnPinB);
  btnStateC = digitalRead(btnPinC);
  btnStateD = digitalRead(btnPinD);
  btnStateE = digitalRead(btnPinE);
  btnStateF = digitalRead(btnPinF);
  btnStateG = digitalRead(btnPinG);
  
  // Run when button state changes, 
  // Run once for each state change
  //
  // 

  //Button A ================ ================ ================ ================ ================
  if(btnStateA != lastBtnStateA){
    if(btnStateA == LOW){
        //========send trigger===========
        Serial.println("btn A On");

    } else if (btnStateA == HIGH){
      Serial.println("btn A OFF");
    }
    delay(delayConst);
    
  }
  lastBtnStateA = btnStateA;

 //Button B ================ ================ ================ ================ ================
 if(btnStateB != lastBtnStateB){
    if(btnStateB == LOW){
        //========send trigger===========
        Serial.println("btn B On");

    } else if (btnStateB == HIGH){
      Serial.println("btn B OFF");
    }
    delay(delayConst);
    
  }
  lastBtnStateB = btnStateB;

 //Button C ================ ================ ================ ================ ================
 if(btnStateC != lastBtnStateC){
    if(btnStateC == LOW){
        //========send trigger===========
        Serial.println("btn C On");

    } else if (btnStateC == HIGH){
      Serial.println("btn C OFF");
    }
    delay(delayConst);
    
  }
  lastBtnStateC = btnStateC;

 //Button D ================ ================ ================ ================ ================
 if(btnStateD != lastBtnStateD){
    if(btnStateD == LOW){
        //========send trigger===========
        Serial.println("btn D On");

    } else if (btnStateD == HIGH){
      Serial.println("btn D OFF");
    }
    delay(delayConst);
    
  }
  lastBtnStateD = btnStateD;

 //Button E ================ ================ ================ ================ ================
 if(btnStateE != lastBtnStateE){
    if(btnStateE == LOW){
        //========send trigger===========
        Serial.println("btn E On");

    } else if (btnStateE == HIGH){
      Serial.println("btn E OFF");
    }
    delay(delayConst);
    
  }
  lastBtnStateE = btnStateE;

 //Button F ================ ================ ================ ================ ================
 if(btnStateF != lastBtnStateF){
    if(btnStateF == LOW){
        //========send trigger===========
        Serial.println("btn F On");

    } else if (btnStateF == HIGH){
      Serial.println("btn F OFF");
    }
    delay(delayConst);
    
  }
  lastBtnStateF = btnStateF;

 //Button G ================
 if(btnStateG != lastBtnStateG){
    if(btnStateG == LOW){
        //========send trigger===========
        Serial.println("btn G On");

    } else if (btnStateG == HIGH){
      Serial.println("btn G OFF");
    }
    delay(delayConst);
    
  }
  lastBtnStateG = btnStateG;


 
}
