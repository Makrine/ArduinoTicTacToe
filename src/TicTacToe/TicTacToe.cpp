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
      if(board[3*i+j] == BOT){
        x_count++;
      } else if(board[3*i+j] == HUMAN){
        o_count++;
      }
    }
    if(x_count == 3) return BOT;
    else if(o_count == 3) return HUMAN;
    else x_count = o_count = 0;
  }
  
  // check cols
  for(i = 0; i < 3; i++){
    for(j = 0; j < 3; j++){
      if(board[3*j+i] == BOT){
        x_count++;
      } else if(board[3*j+i] == HUMAN){
        o_count++;
      }
    }
    if(x_count == 3) return BOT;
    else if(o_count == 3) return HUMAN;
    else x_count = o_count = 0;
  }

  // check diagonals
  for(i = 0; i < 3; i++){
    if(board[3*i+i] == BOT){
      x_count++;
    } else if(board[3*i+i] == HUMAN){
      o_count++;
    }
  }
  if(x_count == 3) return BOT;
  else if(o_count == 3) return HUMAN;
  else x_count = o_count = 0;
  
  for(i = 0; i < 3; i++){
    if(board[3*i+2-i] == BOT){
      x_count++;
    } else if(board[3*i+2-i] == HUMAN){
      o_count++;
    }
  }
  if(x_count == 3) return BOT;
  else if(o_count == 3) return HUMAN;
  else x_count = o_count = 0;

  return 0;
}

void TicTacToe::botTakeAction(uint8_t action)
{
    board[action] = BOT;
}

void TicTacToe::humanTakeAction(uint8_t action)
{
    board[action] = HUMAN;
}