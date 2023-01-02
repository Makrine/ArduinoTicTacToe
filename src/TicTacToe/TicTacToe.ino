
#include "Keypad.h"
#include "LedMatrixController.h"
#include <aifes.h>
#if __AVR__
#include <aifes_avr_pgm.h>
#endif // __AVR__
#if __arm__ && defined USE_CMSIS_ACCELERATION_ON_ARM
#include <aifes_cmsis.h>
#endif // __arm__

#define  O   -64  // (value=-64; shift=6; zero_point=0) -> -1.0f
#define  X    64  // (value=64; shift=6; zero_point=0)  ->  1.0f

// The TicTacToe board. Can be X (AI), O (Player) or 0 (Free).
int8_t board[9];



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



// Returns the winner of the TicTacToe board (X / O). If there is no winner, it returns 0.
int8_t winner(int8_t *board)
{
  int i, j;
  
  int x_count = 0;
  int o_count = 0;
  
  // check rows
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      if(board[3*i+j] == X){
        x_count++;
      } else if(board[3*i+j] == O){
        o_count++;
      }
    }
    if(x_count == 3) return X;
    else if(o_count == 3) return O;
    else x_count = o_count = 0;
  }
  
  // check cols
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      if(board[3*j+i] == X){
        x_count++;
      } else if(board[3*j+i] == O){
        o_count++;
      }
    }
    if(x_count == 3) return X;
    else if(o_count == 3) return O;
    else x_count = o_count = 0;
  }

  // check diagonals
  for(i = 0; i < 3; i++){
    if(board[3*i+i] == X){
      x_count++;
    } else if(board[3*i+i] == O){
      o_count++;
    }
  }
  if(x_count == 3) return X;
  else if(o_count == 3) return O;
  else x_count = o_count = 0;
  
  for(i = 0; i < 3; i++){
    if(board[3*i+2-i] == X){
      x_count++;
    } else if(board[3*i+2-i] == O){
      o_count++;
    }
  }
  if(x_count == 3) return X;
  else if(o_count == 3) return O;
  else x_count = o_count = 0;

  return 0;
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
      int action = key - '0' - 1;

      if(board[action] == 0) return action;
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
  // Reset the board
  for(i = 0; i < 9; i++){
    board[i] = 0.0f;
  }

  // TicTacToe agent
  for(i = 0; i < 5; i++){
    action = getHumanInput();

    board[action] = O;
    
    INDEX_LED hLed = get2DIndex(action);
    ledController.LedState(ledController.RED, hLed, 255);


    if(winner(board) == O){
      // wow
      break;
    }

    
    action = run_ai_agent(board);
  
    
    board[action] = X;
    INDEX_LED bLed = get2DIndex(action);
    ledController.LedState(ledController.BLUE, bLed, 255);
    
    if(winner(board) == X){
        // lost
      break;
    }
  }

}
