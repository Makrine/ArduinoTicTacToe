#include "Keypad.h"
#include "LedMatrixController.h"

const byte ROWS = 3; 
const byte COLS = 3;
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

byte rowPins[ROWS] = {2, 1, 0}; 
byte colPins[COLS] = {5, 4, 3};


short waitTime = 500;
byte refreshRate = 1;

byte myRows[3] = {13, 12, 8};
byte colsR[3] = {11, 10, 9};
byte colsB[3] = {A3, A4, 6};
byte colsG[3] = {A0, A1, A2};

byte potPin = A5;
byte turnLed = 7;

LedController ledController(myRows, colsR, colsB, colsG, 3, 3, refreshRate);

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup()
{
  //Serial.begin(9600);
  pinMode(potPin, INPUT);
  pinMode(turnLed, OUTPUT);
}

void loop()
{
  int rawPotValue = analogRead(potPin);
  byte potValue = map(rawPotValue, 0, 1023, 0, 255);




  char key = keypad.getKey();

  if(key == '1')
  {
    if(!ledController.IsOn(0, 0))
      ledController.LedState(ledController.BLUE, 0, 0, 255);
    else
      ledController.LedState(ledController.RED, 0, 0, 0);
  }
  else if(key == '2')
  {
    if(!ledController.IsOn(0, 1))
      ledController.LedState(ledController.BLUE, 0, 1, 255);
    else
      ledController.LedState(ledController.RED, 0, 1, 0);
  }
  else if(key == '3')
  {
    if(!ledController.IsOn(0, 2))
      ledController.LedState(ledController.BLUE, 0, 2, 255);
    else
      ledController.LedState(ledController.RED, 0, 2, 0);
  }

  if(key == '4')
  {
    if(!ledController.IsOn(1, 0 ))
      ledController.LedState(ledController.BLUE, 1, 0, 255);
    else
      ledController.LedState(ledController.RED, 1, 0, 0);
  }
  else if(key == '5')
  {
    if(!ledController.IsOn(1, 1))
      ledController.LedState(ledController.BLUE, 1, 1, 255);
    else
      ledController.LedState(ledController.RED, 1, 1, 0);
  }
  else if(key == '6')
  {
    if(!ledController.IsOn(1, 2))
      ledController.LedState(ledController.BLUE, 1, 2, 255);
    else
      ledController.LedState(ledController.RED, 1, 2, 0);
  }

  if(key == '7')
  {
    if(!ledController.IsOn(2, 0))
      ledController.LedState(ledController.BLUE, 2, 0, 255);
    else
      ledController.LedState(ledController.RED, 2, 0, 0);
  }
  else if(key == '8')
  {
    if(!ledController.IsOn(2, 1))
      ledController.LedState(ledController.BLUE, 2, 1, 255);
    else
      ledController.LedState(ledController.RED, 2, 1, 0);
  }
  else if(key == '9')
  {
    if(!ledController.IsOn(2, 2))
      ledController.LedState(ledController.BLUE, 2, 2, 255);
    else
      ledController.LedState(ledController.RED, 2, 2, 0);
  }

  ledController.CheckStatesMatrix();
}