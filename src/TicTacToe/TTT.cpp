#ifndef TTT
#define TTT

#include "TTT.h"


TicTacToe::TicTacToe(int dimension, int randomSeedPin)
{
    _dimension = dimension;

    // initialize the game board of the size of dimension
    board = new Player*[dimension];
    for(int i = 0; i < dimension; i++)
    {
        board[i] = new Player[dimension]{E};
        
    }

    // initialize available indexes. Its size is dimension*dimesnsion 
    // and has 2 elements each row: {board row index, board column index}
    _availableIndexesSize = dimension*dimension;
    _availableIndexes = new INDEX[_availableIndexesSize];
    int i  = 0, j = 0;
    for(int k = 0; k < _availableIndexesSize; k++)
    {
        INDEX index(i, j++);
        //_availableIndexes2.push_back(index);
        _availableIndexes[k] = index;
        if(j == 3) {i++; j = 0;}
    }

    randomSeed(analogRead(randomSeedPin));
}

// INDEX TicTacToe::GetPlayerInput()
// {
//     // get input
//     int row, column;
//     cout << "Enter index (separate with SPACE): ";

//     cin >> row >> column;
//     INDEX index(row, column);

//     return index;
// }

bool TicTacToe::HumanMove(INDEX index, Player type)
{
    
    // if the index is available, update the board and return true
    if(IsAvailable(index))
    {
        Updateboard(index, type);
        return true;
    }      
    
    // else notify that that the board is not available
    return false;

}

void TicTacToe::BotMove(Player type)
{
    int randIndex = RandomNumber();

    botMove = _availableIndexes[randIndex];
    Updateboard(_availableIndexes[randIndex], type);
    

}

int TicTacToe::RandomNumber()
{
  // The human should slightly rotate the potentiometer every time they start a new game
  // so that the bot doesn't play the same way

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

void TicTacToe::PrintBoard()
{
    for(int i = 0; i < _dimension; i++)
    {
        for(int j = 0; j < _dimension; j++)
        {
            Serial.print(board[i][j]);
        }
        Serial.println();
    }
}
bool TicTacToe::IsGameOverBool()
{
  return _isGameOver;
}
Player TicTacToe::IsGameOver()
{
    Player p;

    // Draw
    if(_availableIndexesSize <= 0) return D;

    // horizonals
    p = board[0][0];
    if(p != E)
    { 
      if(p == board[0][1] && p == board[0][2]) { _isGameOver = true; return p;}
    }
    p = board[1][0];
    if(p != E)
    { 
      if(p == board[1][1] && p == board[1][2]) { _isGameOver = true; return p;}
    }
    p = board[2][0];
    if(p != E)
    { 
      if(p == board[2][1] && p == board[2][2]) { _isGameOver = true; return p;}
    }

    // verticals
    p = board[0][0];
    if(p != E)
    { 
      if(p == board[1][0] && p == board[2][0]) { _isGameOver = true; return p;}
    }
    p = board[0][1];
    if(p != E)
    { 
      if(p == board[1][1] && p == board[2][1]) { _isGameOver = true; return p;}
    }
    p = board[0][2];
    if(p != E)
    { 
      if(p == board[1][2] && p == board[2][2]) { _isGameOver = true; return p;}
    }


    // identity
    p = board[0][0];
    if(p != E)
    { 
      if(p == board[1][1] && p == board[2][2]) { _isGameOver = true; return p;}
    }

    // reverse identity
    p = board[0][2];
    if(p != E)
    { 
      if(p == board[1][1] && p == board[2][0]) { _isGameOver = true; return p;}
    }

    return E;
}

void TicTacToe::RemoveAvailableIndex(INDEX index)
{
    int foundIndex = -1;
    for(int i = 0; i < _availableIndexesSize; i++)
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
        for(int i = foundIndex; i < _availableIndexesSize; i++)
            _availableIndexes[i] = _availableIndexes[i+1];
    }
}

bool TicTacToe::IsXTurn()
{
    return _xTurn;
}


#endif