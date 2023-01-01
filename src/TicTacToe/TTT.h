#ifndef TTT_H
#define TTT_H

#include "Arduino.h"

/// @brief E: Empty, X: X, O: O, D: Draw
enum Player
{
    E = 0, 
    X = 1, 
    O = -1,
    D = 2
};

struct INDEX
{
    int row, column;

    INDEX()
    {
        row = -1;
        column = -1;
    }
    INDEX(int r, int c)
    {
        row = r;
        column = c;
    }
};

class TicTacToe
{
    private:
        
        bool _isGameOver = false;
        int _dimension;
        Player** board;
        int _availableIndexesSize;
        INDEX* _availableIndexes;
        bool _xTurn;

        /// @brief Removes the index from the available indexes list. 
        // This is for the bot move so that it chooses the available spot.
        /// @param index 
        void RemoveAvailableIndex(INDEX index);
        /// @brief Returns random number in a range of available indexes count
        /// @return 
        int RandomNumber();
        
    public:
        INDEX botMove;
        INDEX humanMove;
        TicTacToe(int dimension);
        /// @brief Makes the player move on the specified index
        /// @param index index on the board where the player wants to move
        /// @param type X, O. Is the player X or O
        /// @return 
        bool HumanMove(INDEX index, Player type);
        /// @brief Makes the bot move
        /// @param type X, O. Is the bot X or O
        /// @return 
        void BotMoveEasy(Player type);
        /// @brief Checks whether the given index is available
        /// @param index 
        /// @return 
        bool IsAvailable(INDEX index);
        /// @brief Updates the board.
        /// @param index index where the board needs to be updated
        /// @param type was X or O written?
        void Updateboard(INDEX index, Player type);
        /// @brief Checks if the game is over and returns the winner.
        /// if no winner, returns E (Empty)
        /// @return 
        Player IsGameOver();
        /// @brief Returns whether it is X's turn or not
        /// @return 
        bool IsXTurn();
        /// @brief Checks if the game is over.
        /// @return 
        bool IsGameOverBool();
        INDEX IsHumanWinning(Player p);
        void BotMoveMedium(Player p);
        void BotMoveHard(Player p);
};

#endif