
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

byte rowPins[ROWS] = {A3, A4, A5};//{2, 1, 0}; //{A3, A4, A5};//
byte colPins[COLS] = {5, 4, 3};

byte refreshRate = 1;

byte myRows[3] = {13, 12, 8};
byte colsR[3] = {11, 10, 9};
byte colsB[3] = {6, A4, A3};
byte colsG[3] = {A0, A1, A2};

LedController ledController(myRows, colsR, colsB, colsG, 3, 3, refreshRate);

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

TicTacToe ttt = TicTacToe();


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
      int action = key - '0' - 1;

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

void setup() {
  // Init serial port for communication
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect.
  }

  // Init neural network
  init_ai_agent();
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

void loop() {
  uint8_t action;
  uint8_t i, j;


  Reseet();
  ttt.resetBoard();

  // TicTacToe agent
  for(i = 0; i < 5; i++){
    action = getHumanInput();

    ttt.humanTakeAction(action);
    
    INDEX_LED hLed = get2DIndex(action);
    ledController.LedState(ledController.RED, hLed, 255);


    if(ttt.winner() == HUMAN){
      // wow
      break;
    }

    
    action = run_ai_agent(ttt.board);
  
    
    ttt.botTakeAction(Hard, action);

    INDEX_LED bLed = get2DIndex(action);
    ledController.LedState(ledController.BLUE, bLed, 255);
    
    if(ttt.winner() == BOT){
        // lost
      break;
    }
  }

}
