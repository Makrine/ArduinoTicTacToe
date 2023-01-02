#ifndef TicTacToe_H
#define TicTacToe_H

#include "Arduino.h"

#define  O   -64  // (value=-64; shift=6; zero_point=0) -> -1.0f
#define  X    64  // (value=64; shift=6; zero_point=0)  ->  1.0f


class TicTacToe
{
    public:
        int8_t board[9];

        TicTacToe();
        int8_t winner();
        void resetBoard();
};



#endif