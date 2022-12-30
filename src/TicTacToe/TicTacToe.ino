#include "Keypad.h"
#include "LedMatrixController.h"
#include "TTT.h"

const byte ROWS = 3; 
const byte COLS = 3;
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

byte rowPins[ROWS] = {2, 1, 0}; //{A0, A1, A2};
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

TicTacToe ttt(3);

enum Difficulty
{
  Easy, Medium, Hard
};

void setup()
{
  //Serial.begin(9600);
  pinMode(potPin, INPUT);
  int randSeed= analogRead(potPin);
  randomSeed(randSeed);

  // Serial.print("Random Seed: ");
  // Serial.print(randSeed);
  // Serial.println();

  pinMode(turnLed, OUTPUT);
}

void loop()
{

setDifficulty(Easy);

ledController.CheckStatesMatrix();
  
}


void setDifficulty(Difficulty diff)
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

      if(!ttt.HumanMove(ttt.humanMove, X))
        key = NO_KEY;

    }
  }
    


    
    INDEX_LED humanLed(ttt.humanMove.row, ttt.humanMove.column);
    ledController.LedState(ledController.BLUE, humanLed, 255);
    
    Player p = ttt.IsGameOver();

    if(!ttt.IsGameOverBool())
    {
      if(diff == Easy)
      {
        ttt.BotMoveEasy(O);
      }
      else if(diff == Medium)
      {
        ttt.BotMoveMedium(O);
      }
      else if(diff == Hard)
      {
        ttt.BotMoveHard(O);
      }
    INDEX_LED botLed(ttt.botMove.row, ttt.botMove.column);
    ledController.LedState(ledController.RED, botLed, 255);
    p = ttt.IsGameOver();
    if(ttt.IsGameOverBool())
    {
      //ttt.PrintBoard();
    }
    }

  else {
    //ttt.PrintBoard();
    //ledController.LedState(ledController.GREEN, humanLed, 255);
    }
}