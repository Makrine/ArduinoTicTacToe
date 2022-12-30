#ifndef TTT
#define TTT

#include "TTT.h"

#include <iostream>
#include <cstdlib>

using namespace std;

TicTacToe::TicTacToe(int dimension)
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
    
   
}

INDEX TicTacToe::GetPlayerInput()
{
    // get input
    int row, column;
    cout << "Enter index (separate with SPACE): ";

    cin >> row >> column;
    INDEX index(row, column);

    return index;
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

  int playerPoint = 0;
  int empty = 0;
  INDEX emptyIndex;


  // horizontal
  for(int i = 0; i < _dimension; i++)
  {
    for(int j = 0; j < _dimension; j++)
    {
      if(board[i][j] == p)
      {
        playerPoint++;
        //printf("Player at {%d, %d}\n", i, j);
      }
      else if(board[i][j] == E && emptyIndex.row == -1)
      {
        emptyIndex.row = i;
        emptyIndex.column = j;
        //printf("H%d: FIRST Empty at {%d, %d}\n", i, i, j);
      }
      else
      {
        //printf("H%d: BOT or Second Empty at {%d, %d} BREAKING\n", i, i, j);
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
  for(int i = 0; i < _dimension; i++)
  {
    for(int j = 0; j < _dimension; j++)
    {
      if(board[j][i] == p)
      {
        playerPoint++;
        //printf("Player at {%d, %d}\n", i, j);
      }
      else if(board[j][i] == E && emptyIndex.row == -1)
      {
        emptyIndex.row = j;
        emptyIndex.column = i;
        //printf("V%d: FIRST Empty at {%d, %d}\n", i, j, i);
      }
      else
      {
        //printf("V%d: BOT or Second Empty at {%d, %d} BREAKING\n", i, j, i);
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
  for(int i = 0; i < _dimension; i++)
  {
    if(board[i][i] == p)
    {
      playerPoint++;
      //printf("Player at {%d, %d}\n", i, i);
    }
    else if(board[i][i] == E && emptyIndex.row == -1)
    {
      emptyIndex.row = i;
      emptyIndex.column = i;
      //printf("D1: FIRST Empty at {%d, %d}\n", i, i);
    }
    else
    {
      //printf("D1: BOT or Second Empty at {%d, %d} BREAKING\n", i, i);
        playerPoint = 0;
        empty = 0;
        emptyIndex.row = -1;
        emptyIndex.column = -1;
      break;
    }
  }

  if(playerPoint == _dimension - 1) { botMove = emptyIndex; return emptyIndex;}

  // diagonal 2
  for(int i = 0, j = _dimension - 1; i < _dimension && j>=0; i++, j--)
  {
    if(board[j][i] == p)
    {
      playerPoint++;
      //printf("Player at {%d, %d}\n", i, j);
    }
    else if(board[j][i] == E && emptyIndex.row == -1)
    {
      emptyIndex.row = j;
      emptyIndex.column = i;
      //printf("D2: FIRST Empty at {%d, %d}\n", i, j);
    }
    else
    {
      //printf("D2: BOT or Second Empty at {%d, %d} BREAKING\n", j, i);
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
      //cout << "YES\n";
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

    //int random_variable = random(_availableIndexesSize);
    srand((unsigned) time(NULL));
    int random_variable = (rand() % _availableIndexesSize);

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
            //Serial.print(board[i][j]);
            cout << board[i][j];
        }
        //Serial.println();
        cout << endl;
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
    if(_availableIndexesSize <= 0) { _isGameOver = true; return D;}


    // horizonal win

    // get the first element of the row in "cell" and iterate on other elements of that row
    // if the current element is the same as the cell continue, it means this row might have the win
    // else break and set sell to E
    // if after the row iteration is done, check the cell, if it is not E, it means there is a win and return it
    // same with vertical but we check columns
    for(int i = 0; i < _dimension; i++)
    {
      Player cell = board[i][0];
      if(cell == E) continue;
      for (int j = 1; j < _dimension; j++)
      {
        if(board[i][j] == cell)
        {
          //printf("?win for %d at {%d, %d}\n", cell, i, j);
          continue;
        } 
        else
        {
          //printf("row %d NO win because of {%d, %d}\n", i, i, j);
          cell = E;
          break;
        }
      }

      if(cell != E) { _isGameOver = true; return cell;}
    }

    // vertical win
    for(int i = 0; i < _dimension; i++)
    {
      Player cell = board[0][i];
      if(cell == E) continue;
      for (int j = 1; j < _dimension; j++)
      {
        if(board[j][i] == cell)
        {
          //printf("?win for %d at {%d, %d}\n", cell, j, i);
          continue;
        } 
        else
        {
          //printf("column %d NO win because of {%d, %d}\n", i, j, i);
          cell = E;
          break;
        }
      }

      if(cell != E) { _isGameOver = true; return cell;}
    }

    // identity win
    Player cell = board[0][0];
    if(cell == E) return E;
    for (int i = 1; i < _dimension; i++)
    {
      if(board[i][i] == cell) 
      {
        //printf("?win for %d at {%d, %d}\n", cell, i, i);
        continue;
      }
      else
      {
        //printf("identity NO win because of {%d, %d}\n", i, i);
        cell = E;
        break;
      }
    }
    if(cell != E) { _isGameOver = true; return cell;}
    
    // reverse identity win
    cell = board[0][2];
    if(cell == E) return E;

    for (int i = _dimension - 2, j = 1; i >= 0 && j < _dimension; i--, j++)
    {
      if(board[j][i] == cell)
      {
        //printf("?win for %d at {%d, %d}\n", cell, j, i);
        continue;
      }
      else
      {
        //printf("Reverse identity NO win because of {%d, %d}\n", j, i);
        cell = E;
        break;
      }
    }
    if(cell != E) { _isGameOver = true; return cell;}

    return E;

    // // horizonals
    // p = board[0][0];
    // if(p != E)
    // { 
    //   if(p == board[0][1] && p == board[0][2]) { _isGameOver = true; return p;}
    // }
    // p = board[1][0];
    // if(p != E)
    // { 
    //   if(p == board[1][1] && p == board[1][2]) { _isGameOver = true; return p;}
    // }
    // p = board[2][0];
    // if(p != E)
    // { 
    //   if(p == board[2][1] && p == board[2][2]) { _isGameOver = true; return p;}
    // }

    // // verticals
    // p = board[0][0];
    // if(p != E)
    // { 
    //   if(p == board[1][0] && p == board[2][0]) { _isGameOver = true; return p;}
    // }
    // p = board[0][1];
    // if(p != E)
    // { 
    //   if(p == board[1][1] && p == board[2][1]) { _isGameOver = true; return p;}
    // }
    // p = board[0][2];
    // if(p != E)
    // { 
    //   if(p == board[1][2] && p == board[2][2]) { _isGameOver = true; return p;}
    // }


    // // identity
    // p = board[0][0];
    // if(p != E)
    // { 
    //   if(p == board[1][1] && p == board[2][2]) { _isGameOver = true; return p;}
    // }

    // // reverse identity
    // p = board[0][2];
    // if(p != E)
    // { 
    //   if(p == board[1][1] && p == board[2][0]) { _isGameOver = true; return p;}
    // }

    // return E;
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

void TicTacToe::BotMoveHard(Player p)
{

}

enum Difficulty
{
  Easy, Medium, Hard, PvP
};

void setDifficulty(TicTacToe &ttt, Difficulty diff, bool &humanStarts)
{
  // if the game is over, flash leds and just don't continue
  //while(ttt.IsGameOverBool()) { ledController.CheckStatesMatrix(); delay(20);}

  if(humanStarts)
  {
    INDEX input = ttt.GetPlayerInput();

    while(!ttt.HumanMove(input, X))
      input = ttt.GetPlayerInput();

    // check if the game is over
    Player p = ttt.IsGameOver();
    
    if(p != E)
    {
    	printf("%d WON or DRAW", p);
    	exit(0);
    }
  }

  humanStarts = true;

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


      Player p = ttt.IsGameOver();
      if(p != E)
      {
        printf("%d WON or DRAW", p);
        exit(0);
      }
      ttt.PrintBoard();
      
    }
    // if the second player is a humam
    else
    {
        INDEX input = ttt.GetPlayerInput();

        while(!ttt.HumanMove(input, X))
          input = ttt.GetPlayerInput();
  

        Player p = ttt.IsGameOver();
        if(p != E)
        {
          printf("%d WON or DRAW", p);
          exit(0);
        }
  
    }
    
    
}


int main()
{
    TicTacToe ttt(3);
    bool humanStarts = false;
    while(true) setDifficulty(ttt, Easy, humanStarts);

  printf("\nGAME OVER\n");
  return 0;
}
#endif