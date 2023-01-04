
#include "Keypad.h"
#include "LedMatrixController.h"
#include <aifes.h>

#include "TicTacToe.h"

#if __AVR__
#include <aifes_avr_pgm.h>
#endif // __AVR__
#if __arm__ && defined USE_CMSIS_ACCELERATION_ON_ARM
#include <aifes_cmsis.h>
#endif // __arm__





const byte ROWS = 3; 
const byte COLS = 3;
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

byte rowPins[ROWS] = {7, 6, 5}; 
byte colPins[COLS] = {4, 3, 2}; 

byte refreshRate = 1;

byte myRows[3] = {13, 12, 8};
byte colsR[3] = {A2, A1, A0};
byte colsB[3] = {9, 11, 10};
byte colsG[3] = {A3, A4, A5};

LedController ledController(myRows, colsR, colsG, colsB, 3, 3, refreshRate);

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

TicTacToe ttt = TicTacToe(true);

byte randomNumPin = A7;
byte potPin = A6;
byte startPin = 0;
byte togglePin = 1;

bool started = false;
bool xStarts = true;
Mode mode = Easy;

void setup() {
  // Init neural network
  init_ai_agent();

  // Init rand seed from unconnected analog pin
  int randSeed= analogRead(randomNumPin);
  randomSeed(randSeed);

  pinMode(randomNumPin, INPUT);
  pinMode(potPin, INPUT);
  pinMode(startPin, INPUT_PULLUP);
  pinMode(togglePin, INPUT_PULLUP);

}
void loop() {

  if(started)
    GAME(xStarts, mode);
  
  else
    selectMode();

}

void selectMode()
{
  int startNotPressed = digitalRead(startPin);
  int toggleVal       = digitalRead(togglePin);
  int level           = analogRead(potPin);

  level = map(level, 0, 1023, 0, 255);

  if(level < 64) mode = PvP;
  else if(level < 128) mode = Easy;
  else if(level < 192) mode = Medium;
  else mode = Hard;

  if(toggleVal) xStarts = true;
  else xStarts = false;
  if(!startNotPressed)
  {
    started = true;
  }
}




void Reseet()
{
  for(byte i = 0; i < 3; i++)
  {
    for(byte j =0; j < 3; j++)
    {
      INDEX_LED index(i, j);
      ledController.LedState(ledController.RED, index, 0);
      ledController.LedState(ledController.BLUE, index, 0);
    }
  }
  
}


uint8_t getHumanInput()
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
      uint8_t action = key - '0' - 1;

      if(ttt.board[action] == 0) return action;
      else key = NO_KEY;
       
    }
  }
      
}


INDEX_LED get2DIndex(int index)
{
  for(byte i = 0; i < 3; i++)
  {
    for(byte j =0; j < 3; j++)
    {
      if(index == i*3 + j)
      {
        INDEX_LED led(i, j);
        return led;
      }
    }
  }
}
void GAME(bool &humanStarts, Mode mode)
{
  while(ttt.gameOver) {ledController.CheckStatesMatrix(); delay(20);}

  uint8_t action;

  // Reseet();
  // ttt.resetBoard();

  // TicTacToe agent
  while(!ttt.gameOver)
  {

    if(humanStarts)
    {
      action = getHumanInput();

      ttt.humanTakeAction(action);
      
      INDEX_LED hLed = get2DIndex(action);
      ledController.LedState(ledController.RED, hLed, 255);

      int8_t win = ttt.winner();

      if(win == HUMAN){
        // wow
        break;
      }
      else if(win == Draw)
      {
        break;
      }
    }

    humanStarts = true;
    
    if(mode == PvP)
    {
      action = getHumanInput();
    }
    else if(mode == Hard)
    {
      action = run_ai_agent(ttt.board);
    }
    
  
    
    action = ttt.botTakeAction(mode, action);

    INDEX_LED bLed = get2DIndex(action);
    ledController.LedState(ledController.BLUE, bLed, 255);
    
    int8_t win = ttt.winner();

    if(win == BOT){
      // lost
      break;
    }
    else if(win == Draw)
    {
      break;
    }
  }
}
