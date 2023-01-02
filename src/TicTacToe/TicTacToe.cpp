#include "TicTacToe.h"

TicTacToe::TicTacToe()
{
    resetBoard();
}

void TicTacToe::resetBoard()
{
    for(uint8_t i = 0; i < 9; i++) board[i] = 0.0f;
}

int8_t TicTacToe::winner()
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