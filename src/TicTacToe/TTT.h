#include <vector>

enum Player
{
    E, X, O
};

struct INDEX
{
    int row, column;

    INDEX(int r, int c)
    {
        row = r;
        column = c;
    }
};

class TicTacToe
{
    private:
        int _dimension;
        Player** board;
        int _availableIndexesSize;
        std::vector<INDEX> _availableIndexes2;
        int** _availableIndexes;
        bool _xTurn;

        /// @brief Removes the index from the available indexes list. 
        // This is for the bot move so that it chooses the available spot.
        /// @param index 
        void RemoveAvailableIndex(INDEX index);
        /// @brief Returns random number in a range of available indexes count
        /// @return 
        int RandomNumber();
        
    public:     
        TicTacToe(int dimension);
        /// @brief Makes the player move on the specified index
        /// @param index index on the board where the player wants to move
        /// @param type X, O. Is the player X or O
        /// @return 
        bool PlayerMove(INDEX index, Player type);
        /// @brief Makes the bot move
        /// @param type X, O. Is the bot X or O
        /// @return 
        void BotMove(Player type);
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
        

        // Methods specific for C++
        INDEX GetPlayerInput();
        void PrintBoard();
};