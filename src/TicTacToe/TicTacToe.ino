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

byte rowPins[ROWS] = {2, 1, 0};
byte colPins[COLS] = {5, 4, 3};

byte refreshRate = 1;

byte myRows[3] = {13, 12, 8};
byte colsR[3] = {11, 10, 9};
byte colsB[3] = {6, A4, A3};
byte colsG[3] = {A0, A1, A2};

byte randomNumPin = A5;
byte turnLed = 7;

LedController ledController(myRows, colsR, colsB, colsG, 3, 3, refreshRate);

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

TicTacToe ttt(3);

enum MODE
{
  Easy, Medium, Hard, PvP
};

void setup()
{
  pinMode(randomNumPin, INPUT);
  int randSeed= analogRead(randomNumPin);
  randomSeed(randSeed);
  pinMode(turnLed, OUTPUT);
}
bool humanStarts = true;

void loop()
{

  setMode(Medium, humanStarts);

  ledController.CheckStatesMatrix();
  
}


void setMode(MODE diff, bool &humanStarts)
{

  // if the game is over, flash leds and just don't continue
  while(ttt.IsGameOverBool()) { ledController.CheckStatesMatrix(); delay(20);}

  if(humanStarts)
  {
    getHumanInput(X);
  
    // once the legit input is given, turn on the corresponding led
    INDEX_LED humanLed(ttt.humanMove.row, ttt.humanMove.column);
    ledController.LedState(ledController.BLUE, humanLed, 255);
    
    // check if the game is over
    Player p = ttt.IsGameOver();    
  }
 
  humanStarts = true;
  

  // if the game is not over, make the second player move
  if(!ttt.IsGameOverBool())
  {
    // if the second player is the bot, make the corresponding move 
    // depending on the level
    if(diff != PvP)
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

      // turn on the bot's led
      INDEX_LED botLed(ttt.botMove.row, ttt.botMove.column);
      ledController.LedState(ledController.RED, botLed, 255);

      
    }
    // if the second player is a humam
    else
    {
        getHumanInput(O);
  
        // once the legit input is given, turn on the corresponding led
        INDEX_LED humanLed(ttt.humanMove.row, ttt.humanMove.column);
        ledController.LedState(ledController.RED, humanLed, 255);
  
    }
    Player p = ttt.IsGameOver();
  
  }

}


void getHumanInput(Player p)
{
  // get the player input
  char key = keypad.getKey();

  // wait for the player input
  while(key == NO_KEY)
  {
    // keeping the recently on leds turned on
    ledController.CheckStatesMatrix();

    key = keypad.getKey();

    // if the human pressed the key, check if that spot is avaialble on the board
    if(key != NO_KEY)
    {
      // get board indexes from the key
      translateHumanInput(key);

      // if the spot isn't available, assing NO_KEY so that it will wait for another input
      if(!ttt.HumanMove(ttt.humanMove, p))
        key = NO_KEY;

    }
  }
}

void translateHumanInput(char key)
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