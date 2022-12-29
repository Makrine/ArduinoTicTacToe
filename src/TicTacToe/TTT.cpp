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

    // Horizontal win

    // If the sum of the row equels the dimension or dimension * 2, it's a win.
    // e.g.: 
    // XXX
    // EEE
    // OOE
    // here the sum of the first row will be 3 (dimension = 3) because in Player X = 1. if it was O who won then it'd be 6.
    // for(int i = 0; i < _dimension; i++)
    // {    
    //     int rowSum = 0;
        
    //     for(int j = 0; j < _dimension; j++)
    //     {
    //         p = board[i][j];
    //         // check if the cell is empty so we don't go through all row if just one cell is empty already
    //         if(p != E) rowSum += p;
    //         else 
    //         {
    //             rowSum = 0;
    //             break;
    //         }
    //     }

    //     if(rowSum == _dimension || rowSum == _dimension * 2)
    //     {
    //         _isGameOver = true;
    //         Serial.println("Horizontal WIN");
    //         return p;
    //     }
        
    // }

    // // Vertical win

    // for(int i = 0; i < _dimension; i++)
    // {
    //     int colSum = 0;

    //     for(int j = 0; j < _dimension; j++)
    //     {
    //         p = board[j][i];
    //         // check if the cell is empty so we don't go through all row if just one cell is empty already
    //         if(p != E) colSum += p;
    //         else
    //         {
    //             colSum = 0;
    //             break;
    //         }
    //     }
    //     if(colSum == _dimension || colSum == _dimension * 2)
    //     {
    //         _isGameOver = true;
    //         Serial.println("Vertical WIN");
    //         return p;
    //     }
        
    // }

    // // identity matrix win

    // int identitySum = 0;
    // for(int i = 0; i < _dimension; i++)
    // {

    //     p = board[i][i];
    //     if(p != E) identitySum += p;
    //     else
    //     {
    //         identitySum = 0;
    //         break;
    //     }

    //     if(identitySum == _dimension || identitySum == _dimension * 2)
    //     {
    //         _isGameOver = true;
    //         Serial.println("Identity WIN");
    //         return p;
    //     }
    // }

    // reverse identity matrix win
    // int reverseIdentitySum = 0;
    // for(int i = 0, j = _dimension - 1; i < _dimension && j >= 0; i++, j--)
    // {
    //     p = board[i][j];
    //     if(p != E) {
    //       Serial.println(p);
    //       reverseIdentitySum += p;
    //       }
    //     else 
    //     {
    //         Serial.println("ZEROED");          
    //         reverseIdentitySum = 0;
    //         break;
    //     }

    //     if(reverseIdentitySum == _dimension || reverseIdentitySum == _dimension * 2)
    //     { 
    //         _isGameOver = true;
    //         Serial.println("Reverse Identity WIN");
    //         return p;
    //     }
    // }


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


// int main()
// {
//     TicTacToe ttt(3);


//     while(true)
//     {
//         INDEX index = ttt.GetPlayerInput();

//         while(!ttt.PlayerMove(index, X))
//         {
//             index = ttt.GetPlayerInput();
//         }
//         Player p = ttt.IsGameOver();
//         if(p != E) 
//         {
//             ttt.PrintBoard();
//             if(p == D)
//             {
//                 cout << "DRAW!";
//             }
//             else if (p == X)
//             {
//                 cout << "X" << " WON!";
//             }
            
//             else cout << "O" << " WON!";
//             break;
//         }

//         ttt.BotMove(O);
//         p = ttt.IsGameOver();
//         ttt.PrintBoard();

//         if(p != E) 
//         {
//             if(p == D)
//             {
//                 cout << "DRAW!";
//             }
//             else if (p == X)
//             {
//                 cout << "X" << " WON!";
//             }
            
//             else cout << "O" << " WON!";
//             break;
//         }
//     }
    

//     return 0;
// }

#endif