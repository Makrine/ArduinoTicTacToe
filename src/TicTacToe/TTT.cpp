#include <iostream>
#include "TTT.h"

#include <ctime>

using namespace std;

ostream& operator<<(ostream& os,
                    const vector<INDEX>& vector)
{
    for (auto element : vector) {
        os << "{" << element.row << ", " << element.column << "}";
    }
    return os;
}


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
    _availableIndexes = new int*[_availableIndexesSize];
    int i  = 0, j = 0;
    for(int k = 0; k < _availableIndexesSize; k++)
    {
        INDEX index(i, j);
        _availableIndexes2.push_back(index);
        _availableIndexes[k] = new int[2]{i, j++};
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

bool TicTacToe::PlayerMove(INDEX index, Player type)
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

    Updateboard(_availableIndexes2[randIndex], type);

}

int TicTacToe::RandomNumber()
{
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int random_variable = std::rand()/((RAND_MAX + 1u)/_availableIndexesSize);
    
    return random_variable;
}
bool TicTacToe::IsAvailable(INDEX index)
{
    // check if index is outside of bounds
    if(index.row >= _dimension || index.column >= _dimension) return false;

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
            cout << board[i][j];
        }
        cout << endl;
    }
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
    for(int i = 0; i < _dimension; i++)
    {    
        int rowSum = 0;
        
        for(int j = 0; j < _dimension; j++)
        {
            p = board[i][j];
            // check if the cell is empty so we don't go through all row if just one cell is empty already
            if(p != E) rowSum += p;
            else 
            {
                rowSum = 0;
                break;
            }
        }

        if(rowSum == _dimension || rowSum == _dimension * 2)
        {
            return p;
        }
        
    }

    // Vertical win

    for(int i = 0; i < _dimension; i++)
    {
        int colSum = 0;

        for(int j = 0; j < _dimension; j++)
        {
            p = board[j][i];
            // check if the cell is empty so we don't go through all row if just one cell is empty already
            if(p != E) colSum += p;
            else
            {
                colSum = 0;
                break;
            }
        }
        if(colSum == _dimension || colSum == _dimension * 2)
        {
            return p;
        }
        
    }

    // identity matrix win

    for(int i = 0; i < _dimension; i++)
    {
        int identitySum = 0;

        p = board[i][i];
        if(p != E) identitySum += p;
        else
        {
            identitySum = 0;
            break;
        }

        if(identitySum == _dimension || identitySum == _dimension * 2)
        {
            return p;
        }
    }

    // reverse identity matrix win

    for(int i = 0, j = _dimension - 1; i < _dimension && j >= 0; i++, j--)
    {
        int reverseIdentitySum = 0;

        p = board[i][j];
        if(p != E) reverseIdentitySum += p;
        else 
        {
            reverseIdentitySum = 0;
            break;
        }

        if(reverseIdentitySum == _dimension || reverseIdentitySum == _dimension * 2)
        { 
            return p;
        }
    }

    return E;
}

void TicTacToe::RemoveAvailableIndex(INDEX index)
{
    int len = _availableIndexes2.size();
    for(int i = 0; i < len; i++)
    {
        if(_availableIndexes2[i].row == index.row && _availableIndexes2[i].column == index.column)
        {
            _availableIndexes2.erase(_availableIndexes2.begin() + i);
        }
    }
    _availableIndexesSize--;
}

bool TicTacToe::IsXTurn()
{
    return _xTurn;
}


int main()
{
    TicTacToe ttt(3);


    while(true)
    {
        INDEX index = ttt.GetPlayerInput();

        while(!ttt.PlayerMove(index, X))
        {
            index = ttt.GetPlayerInput();
        }
        Player p = ttt.IsGameOver();
        if(p != E) 
        {
            ttt.PrintBoard();
            if(p == D)
            {
                cout << "DRAW!";
            }
            else if (p == X)
            {
                cout << "X" << " WON!";
            }
            
            else cout << "O" << " WON!";
            break;
        }

        ttt.BotMove(O);
        p = ttt.IsGameOver();
        ttt.PrintBoard();

        if(p != E) 
        {
            if(p == D)
            {
                cout << "DRAW!";
            }
            else if (p == X)
            {
                cout << "X" << " WON!";
            }
            
            else cout << "O" << " WON!";
            break;
        }
    }
    

    return 0;
}