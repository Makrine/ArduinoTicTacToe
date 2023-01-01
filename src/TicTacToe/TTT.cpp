#ifndef TTT
#define TTT

#include "TTT.h"


TicTacToe::TicTacToe(byte dimension)
{
    _dimension = dimension;

    // initialize the game board of the size of dimension
    board = new Player*[dimension];
    for(byte i = 0; i < dimension; i++)
    {
        board[i] = new Player[dimension]{E};
        
    }

    // initialize available indexes. Its size is dimension*dimesnsion 
    // and has 2 elements each row: {board row index, board column index}
    _availableIndexesSize = dimension*dimension;
    _availableIndexes = new INDEX[_availableIndexesSize];
    byte i  = 0, j = 0;
    for(byte k = 0; k < _availableIndexesSize; k++)
    {
        INDEX index(i, j++);
        _availableIndexes[k] = index;
        if(j == 3) {i++; j = 0;}
    }
    
}


bool TicTacToe::HumanMove(INDEX index, Player p)
{
    
    // if the index is available, update the board and return true
    if(IsAvailable(index))
    {
        Updateboard(index, p);
        return true;
    }      
    
    // else notify that that the board is not available
    return false;

}

void TicTacToe::BotMoveEasy(Player type)
{
    int randIndex = RandomNumber();

    botMove = _availableIndexes[randIndex];
    Updateboard(_availableIndexes[randIndex], type);
    

}

INDEX TicTacToe::IsHumanWinning(Player p)
{

  byte playerPoint = 0;
  byte empty = 0;
  INDEX emptyIndex;


  // horizontal
  for(byte i = 0; i < _dimension; i++)
  {
    for(byte j = 0; j < _dimension; j++)
    {
      if(board[i][j] == p)
      {
        playerPoint++;
      }
      else if(board[i][j] == E && emptyIndex.row == -1)
      {
        emptyIndex.row = i;
        emptyIndex.column = j;
      }
      else
      {
        playerPoint = 0;
        empty = 0;
        emptyIndex.row = -1;
        emptyIndex.column = -1;
        break;
      }
      
    }
    if(playerPoint == _dimension - 1) { botMove = emptyIndex; return emptyIndex;}
  }
  
  // vertical
  for(byte i = 0; i < _dimension; i++)
  {
    for(byte j = 0; j < _dimension; j++)
    {
      if(board[j][i] == p)
      {
        playerPoint++;
      }
      else if(board[j][i] == E && emptyIndex.row == -1)
      {
        emptyIndex.row = j;
        emptyIndex.column = i;
      }
      else
      {
        playerPoint = 0;
        empty = 0;
        emptyIndex.row = -1;
        emptyIndex.column = -1;
        break;
      }

      
    }
     if(playerPoint == _dimension - 1) { botMove = emptyIndex; return emptyIndex;}
  }

  // diagonal
  for(byte i = 0; i < _dimension; i++)
  {
    if(board[i][i] == p)
    {
      playerPoint++;
    }
    else if(board[i][i] == E && emptyIndex.row == -1)
    {
      emptyIndex.row = i;
      emptyIndex.column = i;
    }
    else
    {
        playerPoint = 0;
        empty = 0;
        emptyIndex.row = -1;
        emptyIndex.column = -1;
      break;
    }
  }

  if(playerPoint == _dimension - 1) { botMove = emptyIndex; return emptyIndex;}

  // diagonal 2
  for(byte i = 0, j = _dimension - 1; i < _dimension && j>=0; i++, j--)
  {
    if(board[j][i] == p)
    {
      playerPoint++;
    }
    else if(board[j][i] == E && emptyIndex.row == -1)
    {
      emptyIndex.row = j;
      emptyIndex.column = i;
    }
    else
    {
        playerPoint = 0;
        empty = 0;
        emptyIndex.row = -1;
        emptyIndex.column = -1;
      break;
    }
  }

  if(playerPoint == _dimension - 1) { botMove = emptyIndex; return emptyIndex;}

  return emptyIndex;

}

void TicTacToe::BotMoveMedium(Player type)
{
  Player player;
  if(type == X) player = O;
  else player = X;

    INDEX index = IsHumanWinning(player);

    if(index.row != -1)
    {
      Updateboard(index, type);
    }
    else
    {
      int randIndex = RandomNumber();

      botMove = _availableIndexes[randIndex];
      Updateboard(_availableIndexes[randIndex], type);
    }

}

int TicTacToe::RandomNumber()
{

    int random_variable = random(_availableIndexesSize);

    return random_variable;
}
bool TicTacToe::IsAvailable(INDEX index)
{
    // check if index is outside of bounds
    if(index.row >= _dimension || index.column >= _dimension
      || index.row < 0 || index.column < 0
    ) return false;

    // if the board at that index is Empty, it is available
    if(board[index.row][index.column] == E) return true;
    else return false;
}

void TicTacToe::Updateboard(INDEX index, Player type)
{
    // update the board with the X or O, depending on whose turn it is
    board[index.row][index.column] = type;

    // if this move was made by X, it means now it is the O's turn. And vice versa.
    if(type == X) _xTurn = false;
    else          _xTurn = true;

    RemoveAvailableIndex(index);
}

bool TicTacToe::IsGameOverBool()
{
  return _isGameOver;
}

Player TicTacToe::IsGameOver()
{
    Player p;

    // Draw
    if(_availableIndexesSize <= 0) { _isGameOver = true; return D;}


    // horizontal and vertical win
    // we count the rows and cols cell values, if they == +- dimension it means it's a win
    for(byte i = 0; i < _dimension; i++)
    {
      byte sumRow = 0;
      byte sumCol = 0;
      
      for (byte j = 0; j < _dimension; j++)
      {
        sumRow += board[i][j];
        sumCol += board[j][i];
      }

      if(sumRow == _dimension || sumCol == _dimension ) { _isGameOver = true; return X;}
      else if(sumRow == -_dimension || sumCol == -_dimension) { _isGameOver = true; return O;}
    }


    byte sumIdentity = 0;
    byte sumReverseIdentity = 0;
    for(byte i = 0, j = _dimension - 1; i < _dimension && j >=0; i++, j--)
    {
      sumIdentity += board[i][i];
      sumReverseIdentity += board[i][j];

      if(sumIdentity == _dimension || sumReverseIdentity == _dimension)  {_isGameOver = true; return X;}
      else if(sumIdentity == -_dimension || sumReverseIdentity == -_dimension)  {_isGameOver = true; return O;}
    }


    return E;

}

void TicTacToe::RemoveAvailableIndex(INDEX index)
{
    byte foundIndex = -1;
    for(byte i = 0; i < _availableIndexesSize; i++)
    {
        if(_availableIndexes[i].row == index.row && _availableIndexes[i].column == index.column)
        {
            foundIndex = i;
            break;
        }
    }

    if(foundIndex != -1)
    {
        _availableIndexesSize--;

        //shift all the element from index+1 by one position to the left
        for(byte i = foundIndex; i < _availableIndexesSize; i++)
            _availableIndexes[i] = _availableIndexes[i+1];
    }
}

bool TicTacToe::IsXTurn()
{
    return _xTurn;
}

void TicTacToe::BotMoveHard(Player p)
{


}


#endif