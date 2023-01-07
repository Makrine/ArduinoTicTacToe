#ifndef TicTacToe_H
#define TicTacToe_H

#include "Arduino.h"

#define  HUMAN   -64  // (value=-64; shift=6; zero_point=0) -> -1.0f
#define  BOT      64  // (value=64; shift=6; zero_point=0)  ->  1.0f
#define  Draw      3


enum Mode
{
  PvP,
  Easy,
  Medium,
  Hard
};

class TicTacToe
{
    private:
        bool debug;
        uint8_t availableCells[9];
        uint8_t availableCellsSize = 9;

        void removeAvailableIndex(uint8_t cell);
        uint8_t randomCell();
        uint8_t isHumanWinning();

        void printAvailableIndexes();

        void print_tictactoe_board();

    public:
        bool gameOver;
        int8_t board[9];

        TicTacToe(bool debug);
        int8_t winner();
        void resetBoard();

        void humanTakeAction(uint8_t action);
        uint8_t botTakeAction(Mode mode, uint8_t action);
};



#endif