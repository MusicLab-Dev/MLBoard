/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Board entry point
 */

#include <iostream>

#include <MLBoard/Board.hpp>

int main(void)
{
    try {
        ML::Board board;

        board.run();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "\nAn error occured:\n\t" << e.what() << std::endl;
    }
}