#include "Keypad.h"
#include "LedMatrixController.h"
#include "TTT.h"
#include <string.h>
#include "conversion.h"

const byte ROWS = 3; 
const byte COLS = 3;
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

byte rowPins[ROWS] = {A0, A1, A2};//{2, 1, 0}; 
byte colPins[COLS] = {5, 4, 3};


short waitTime = 500;
byte refreshRate = 1;

byte myRows[3] = {13, 12, 8};
byte colsR[3] = {11, 10, 9};
byte colsB[3] = {6, A4, A3};
byte colsG[3] = {A0, A1, A2};

byte potPin = A5;
byte turnLed = 7;

LedController ledController(myRows, colsR, colsB, colsG, 3, 3, refreshRate);

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

TicTacToe ttt(3, A5);

void setup()
{
  Serial.begin(9600);
  pinMode(potPin, INPUT);
  pinMode(turnLed, OUTPUT);
}
bool legit = false;
void loop()
{

while(ttt.IsGameOverBool()) { ledController.CheckStatesMatrix(); delay(20);}

  char key = keypad.getKey();

  while(key == NO_KEY)
  {
    ledController.CheckStatesMatrix();
    key = keypad.getKey();

    if(key != NO_KEY)
    {
      if(key == '1')
    {
      ttt.humanMove.row = 0;
      ttt.humanMove.column = 0;
    }
    else if(key == '2')
    {
      ttt.humanMove.row = 0;
      ttt.humanMove.column = 1;
    }

    else if(key == '3')
    {
      ttt.humanMove.row = 0;
      ttt.humanMove.column = 2;
    }

    else if(key == '4')
    {
      ttt.humanMove.row = 1;
      ttt.humanMove.column = 0;
    }
    else if(key == '5')
    {
      ttt.humanMove.row = 1;
      ttt.humanMove.column = 1;
    }

    else if(key == '6')
    {
      ttt.humanMove.row = 1;
      ttt.humanMove.column = 2;
    }
    else if(key == '7')
    {
      ttt.humanMove.row = 2;
      ttt.humanMove.column = 0;
    }
    else if(key == '8')
    {
      ttt.humanMove.row = 2;
      ttt.humanMove.column = 1;
    }

    else if(key == '9')
    {
      ttt.humanMove.row = 2;
      ttt.humanMove.column = 2;
    }
    }
  }
    


    
    INDEX_LED humanLed(ttt.humanMove.row, ttt.humanMove.column);

    
    ttt.HumanMove(ttt.humanMove, X);
    ledController.LedState(ledController.GREEN, humanLed, 255);
    
    Player p = ttt.IsGameOver();

    if(!ttt.IsGameOverBool())
    {
      ttt.BotMove(O);

    INDEX_LED botLed(ttt.botMove.row, ttt.botMove.column);
    ledController.LedState(ledController.RED, botLed, 255);
    p = ttt.IsGameOver();
    if(ttt.IsGameOverBool())
    {
      ttt.PrintBoard();
    }
    }

  else {
    ttt.PrintBoard();
    ledController.LedState(ledController.GREEN, humanLed, 255);
    }



    // byte** s = ledController.GetStatesMatrix();

    // for(int i = 0; i < 3; i++)
    // {
    //   for(int j = 0; j < 3; j++)
    //   {
    //     Serial.print(s[i][j]);
    //   }
    //   Serial.println();
    // }

  // char key = keypad.getKey();

  // if(key == '1')
  // {
  //   if(!ledController.IsOn(0, 0))
  //     ledController.LedState(ledController.RED, 0, 0, 255);
  //   else
  //     ledController.LedState(ledController.RED, 0, 0, 0);
  // }
  // else if(key == '2')
  // {
  //   if(!ledController.IsOn(0, 1))
  //     ledController.LedState(ledController.RED, 0, 1, 255);
  //   else
  //     ledController.LedState(ledController.RED, 0, 1, 0);
  // }
  // else if(key == '3')
  // {
  //   if(!ledController.IsOn(0, 2))
  //     ledController.LedState(ledController.RED, 0, 2, 255);
  //   else
  //     ledController.LedState(ledController.RED, 0, 2, 0);
  // }

  // if(key == '4')
  // {
  //   if(!ledController.IsOn(1, 0 ))
  //     ledController.LedState(ledController.RED, 1, 0, 255);
  //   else
  //     ledController.LedState(ledController.RED, 1, 0, 0);
  // }
  // else if(key == '5')
  // {
  //   if(!ledController.IsOn(1, 1))
  //     ledController.LedState(ledController.BLUE, 1, 1, 255);
  //   else
  //     ledController.LedState(ledController.RED, 1, 1, 0);
  // }
  // else if(key == '6')
  // {
  //   if(!ledController.IsOn(1, 2))
  //     ledController.LedState(ledController.BLUE, 1, 2, 255);
  //   else
  //     ledController.LedState(ledController.RED, 1, 2, 0);
  // }

  // if(key == '7')
  // {
  //   if(!ledController.IsOn(2, 0))
  //     ledController.LedState(ledController.BLUE, 2, 0, 255);
  //   else
  //     ledController.LedState(ledController.RED, 2, 0, 0);
  // }
  // else if(key == '8')
  // {
  //   if(!ledController.IsOn(2, 1))
  //     ledController.LedState(ledController.BLUE, 2, 1, 255);
  //   else
  //     ledController.LedState(ledController.RED, 2, 1, 0);
  // }
  // else if(key == '9')
  // {
  //   if(!ledController.IsOn(2, 2))
  //     ledController.LedState(ledController.BLUE, 2, 2, 255);
  //   else
  //     ledController.LedState(ledController.RED, 2, 2, 0);
  // }
ledController.CheckStatesMatrix();
  
}