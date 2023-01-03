#include "TicTacToe.h"

TicTacToe::TicTacToe(bool d)
{
    resetBoard();
    debug = d;
}

void TicTacToe::resetBoard()
{
    for(uint8_t i = 0; i < 9; i++)
    {
        board[i] = 0.0f;
        availableCells[i] = i;
    }
    availableCellsSize = 9;
}

int8_t TicTacToe::winner()
{
  int i, j;
  
    bool isDraw = true;
    for (i = 0; i < 9; i++)
    {
        if(board[i] == 0)
        {
            isDraw = false;
            break;
        }
    }
    
    if(isDraw) {gameOver = true; return Draw;}


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
    if(x_count == 3) {gameOver = true; return BOT;}
    else if(o_count == 3) {gameOver = true; return HUMAN;}
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
    if(x_count == 3) {gameOver = true; return BOT;}
    else if(o_count == 3) {gameOver = true; return HUMAN;}
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
  if(x_count == 3) {gameOver = true; return BOT;}
  else if(o_count == 3) {gameOver = true; return HUMAN;}
  else x_count = o_count = 0;
  
  for(i = 0; i < 3; i++){
    if(board[3*i+2-i] == BOT){
      x_count++;
    } else if(board[3*i+2-i] == HUMAN){
      o_count++;
    }
  }
  if(x_count == 3) {gameOver = true; return BOT;}
  else if(o_count == 3) {gameOver = true; return HUMAN;}
  else x_count = o_count = 0;

  return 0;
}

uint8_t TicTacToe::botTakeAction(Mode mode, uint8_t action = -1)
{
    if(mode == Easy)
    {
        if(debug)
        {
            Serial.println("EASY MODE");
            Serial.print("SELECTED ACTION: "); Serial.print(action); Serial.println();
        }
        action = availableCells[randomCell()];
        
    }
    else if(mode == Medium)
    {
        action = isHumanWinning();

        if(debug)
        {
            Serial.println();
            Serial.println("Medium MODE, target Action: ");
            Serial.println(action);
            Serial.println();
        }

        // if not winning, place randomly
        if(action == 13) action = availableCells[randomCell()];
    }
    else if(mode == Hard)
    {
        // not really anything
    }
    // PvP
    else
    {

    }
    board[action] = BOT;

    
    removeAvailableIndex(action);
    
    if(debug)
    {
        Serial.println();
        Serial.print("Bot Action: "); Serial.print(action); Serial.println();
        printAvailableIndexes();
        print_tictactoe_board();
    }

    return action;
}

void TicTacToe::humanTakeAction(uint8_t action)
{
    
    board[action] = HUMAN;
    removeAvailableIndex(action);

    if(debug)
    {
        Serial.println();
        Serial.print("Human Action: "); Serial.print(action); Serial.println();
        printAvailableIndexes();
        print_tictactoe_board();
    }
    
}

// Easy and medium levels

void TicTacToe::removeAvailableIndex(uint8_t cell)
{
    uint8_t foundIndex = -1;
    for(uint8_t i = 0; i < availableCellsSize; i++)
    {
        if(availableCells[i] == cell)
        {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex != -1)
    {  
        if(debug)
        {
            Serial.print(availableCells[foundIndex]);
            Serial.print(" Removed from cells");
        }
        
        availableCellsSize--;

        //shift all the element from index+1 by one position to the left
        for(uint8_t i = foundIndex; i < availableCellsSize; i++)
        {
            if(foundIndex == 8) availableCells[i] = -1;
            else availableCells[i] = availableCells[i+1];
        }
            
    }

}

uint8_t TicTacToe::randomCell()
{
    uint8_t randCell = random(availableCellsSize);
    return randCell;
}


void TicTacToe::printAvailableIndexes()
{
    Serial.println();
    Serial.println("Available Cells: ");
    for(uint8_t i = 0; i < availableCellsSize; i++)
    {
        Serial.print(availableCells[i]);
    }
    Serial.println();
}

void TicTacToe::print_tictactoe_board()
{
  uint8_t i, j;

  Serial.print(F("   ------------- \n"));
  for(i = 0; i < 3; i++){
     Serial.print(F(" | "));
    for(j = 0; j < 3; j++){
      if(board[i*3 + j] == HUMAN){
          Serial.print(F("O | "));
      } else if(board[i*3 + j] == BOT){
          Serial.print(F("X | "));
      } else {
          Serial.print(F("  | "));
      }
    }
    Serial.print(F("\n   ------------- \n"));
  }
  Serial.println();
  return;
}


uint8_t TicTacToe::isHumanWinning()
{
    uint8_t i, j;
    
    uint8_t targetAction = 13;
    int playerPoint = 0;

    // horizontal
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
        if(board[3*i+j] == HUMAN)
        {
            playerPoint++;
        }
        else if(board[3*i+j] == 0 && targetAction == 13)
        {
            targetAction = 3*i+j;
        }
        else
        {
            playerPoint = 0;
            targetAction = 13;
            break;
        }
        
        }
        if(playerPoint == 2) { return targetAction;}
    }

    // vertical
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
        if(board[3*j+i] == HUMAN)
        {
            playerPoint++;
        }
        else if(board[3*j+i] == 0 && targetAction == 13)
        {
            targetAction = 3*j+i;
        }
        else
        {
            playerPoint = 0;
            targetAction = 13;
            break;
        }
        
        }
        if(playerPoint == 2) { return targetAction;}
    }

    // diagonal
    for(i = 0; i < 3; i++)
    {
        if(board[3*i+i] == HUMAN)
        {
            playerPoint++;
        }
        else if(board[3*i+i] == 0 && targetAction == 13)
        {
            targetAction = 3*i+i;
        }
        else
        {
            playerPoint = 0;
            targetAction = 13;
            break;
        }
    }

    if(playerPoint == 2) { return targetAction;}

    // diagonal 2
    for(i = 0, j = 2; i < 3 && j>=0; i++, j--)
    {
        if(board[3*j+i] == HUMAN)
        {
            playerPoint++;
        }
        else if(board[3*j+i] == 0 && targetAction == 13)
        {
            targetAction = 3*j+i;
        }
        else
        {
            playerPoint = 0;
            targetAction = 13;
            break;
        }
    }

    if(playerPoint == 2) { return targetAction;}

    return targetAction;
}